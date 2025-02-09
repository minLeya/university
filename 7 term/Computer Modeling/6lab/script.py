import xlrd
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

file_path = '1.xls'

workbook = xlrd.open_workbook(file_path)
sheet = workbook.sheet_by_index(0)

data = []
for row_idx in range(sheet.nrows):
    data.append(sheet.row_values(row_idx))

columns = data[0]
rows = data[1:]
df = pd.DataFrame(rows, columns=columns)

X = df.drop(['Cредний доход на одно домохозяйство', 'Район'], axis=1)
y = df['Cредний доход на одно домохозяйство'].values.reshape(-1, 1)
y_mean = y.mean()
y_std = y.std()
X = (X - X.mean()) / X.std()
y = (y - y.mean()) / y.std()

np.random.seed(42)
indices = np.arange(len(df))
np.random.shuffle(indices)
split_index = int(0.8 * len(df))
train_indices = indices[:split_index]
test_indices = indices[split_index:]

X_train, X_test = X.iloc[train_indices].values, X.iloc[test_indices].values
y_train, y_test = y[train_indices], y[test_indices]

# Базовая модель
class Perceptron_default:
    def __init__(self, input_size, hidden_size, output_size, learning_rate=0.01):
        self.W1 = np.random.randn(input_size, hidden_size) * 0.1
        self.b1 = np.zeros((1, hidden_size))
        self.W2 = np.random.randn(hidden_size, output_size) * 0.1
        self.b2 = np.zeros((1, output_size))
        self.learning_rate = learning_rate
        self.loss = 1
        self.train_losses = []
        self.test_losses = []

    def sigmoid(self, z):
        return 1 / (1 + np.exp(-np.clip(z, -500, 500)))

    def sigmoid_derivative(self, z):
        return z * (1 - z)

    def forward(self, X):
        self.Z1 = np.dot(X, self.W1) + self.b1
        self.A1 = self.sigmoid(self.Z1)
        self.Z2 = np.dot(self.A1, self.W2) + self.b2
        self.A2 = self.Z2  # Линейный выход для регрессии
        return self.A2

    def backward(self, X, y, output):
        m = X.shape[0]
        error = output - y
        dZ2 = error
        dW2 = np.dot(self.A1.T, dZ2) / m
        db2 = np.sum(dZ2, axis=0, keepdims=True) / m
        dZ1 = np.dot(dZ2, self.W2.T) * self.sigmoid_derivative(self.A1)
        dW1 = np.dot(X.T, dZ1) / m
        db1 = np.sum(dZ1, axis=0, keepdims=True) / m

        self.W2 -= self.learning_rate * dW2
        self.b2 -= self.learning_rate * db2
        self.W1 -= self.learning_rate * dW1
        self.b1 -= self.learning_rate * db1

    def train(self, X, y, X_test, y_test, stop_losses, epochs=1000):
        epoch = 0
        while self.loss >= stop_losses:
            output = self.forward(X)
            self.backward(X, y, output)

            self.loss = np.mean((output - y) ** 2)
            test_loss = np.mean((self.forward(X_test) - y_test) ** 2)

            # Запись ошибок для графика
            self.train_losses.append(self.loss)
            self.test_losses.append(test_loss)

            if epoch % 10000 == 0:
                print(f"Эпоха {epoch}, Ошибка на обучении: {self.loss}, Ошибка на тесте: {test_loss}")

            if self.loss < stop_losses:
                print(f"Целевая точность достигнута на эпохе {epoch}")
                break

            epoch += 1

    def save_weights(self, filename="weights_default.npz"):
        np.savez(filename, W1=self.W1, b1=self.b1, W2=self.W2, b2=self.b2)
        print(f"Веса сохранены в {filename}")

    def load_weights(self, filename="weights_default.npz"):
        data = np.load(filename)
        self.W1 = data['W1']
        self.b1 = data['b1']
        self.W2 = data['W2']
        self.b2 = data['b2']
        print(f"Веса загружены из {filename}")

    def predict(self, X):
        return self.forward(X)


# Модель с обновлениями (Adam)
class Perceptron_update:
    def __init__(self, input_size, hidden_size, output_size, learning_rate=0.001, beta1=0.9, beta2=0.999, epsilon=1e-8, lambda_reg=0.01):
        self.W1 = np.random.randn(input_size, hidden_size) * 0.1
        self.b1 = np.zeros((1, hidden_size))
        self.W2 = np.random.randn(hidden_size, output_size) * 0.1
        self.b2 = np.zeros((1, output_size))
        self.learning_rate = learning_rate
        self.beta1 = beta1
        self.beta2 = beta2
        self.epsilon = epsilon
        self.lambda_reg = lambda_reg
        self.m_W1, self.v_W1 = np.zeros_like(self.W1), np.zeros_like(self.W1)
        self.m_b1, self.v_b1 = np.zeros_like(self.b1), np.zeros_like(self.b1)
        self.m_W2, self.v_W2 = np.zeros_like(self.W2), np.zeros_like(self.W2)
        self.m_b2, self.v_b2 = np.zeros_like(self.b2), np.zeros_like(self.b2)
        self.loss = 1
        self.train_losses = []
        self.test_losses = []

    def relu(self, z):
        return np.maximum(0, z)

    def relu_derivative(self, z):
        return np.where(z > 0, 1, 0)

    def forward(self, X):
        self.Z1 = np.dot(X, self.W1) + self.b1
        self.A1 = self.relu(self.Z1)
        self.Z2 = np.dot(self.A1, self.W2) + self.b2
        self.A2 = self.Z2  # Линейный выход для регрессии
        return self.A2

    def backward(self, X, y, output):
        m = X.shape[0]
        error = output - y
        dZ2 = error
        dW2 = np.dot(self.A1.T, dZ2) / m + self.lambda_reg * self.W2 / m
        db2 = np.sum(dZ2, axis=0, keepdims=True) / m
        dZ1 = np.dot(dZ2, self.W2.T) * self.relu_derivative(self.A1)
        dW1 = np.dot(X.T, dZ1) / m + self.lambda_reg * self.W1 / m
        db1 = np.sum(dZ1, axis=0, keepdims=True) / m

        self.m_W1 = self.beta1 * self.m_W1 + (1 - self.beta1) * dW1
        self.v_W1 = self.beta2 * self.v_W1 + (1 - self.beta2) * (dW1 ** 2)
        self.m_b1 = self.beta1 * self.m_b1 + (1 - self.beta1) * db1
        self.v_b1 = self.beta2 * self.v_b1 + (1 - self.beta2) * (db1 ** 2)

        self.m_W2 = self.beta1 * self.m_W2 + (1 - self.beta1) * dW2
        self.v_W2 = self.beta2 * self.v_W2 + (1 - self.beta2) * (dW2 ** 2)
        self.m_b2 = self.beta1 * self.m_b2 + (1 - self.beta1) * db2
        self.v_b2 = self.beta2 * self.v_b2 + (1 - self.beta2) * (db2 ** 2)

        m_W1_hat = self.m_W1 / (1 - self.beta1)
        v_W1_hat = self.v_W1 / (1 - self.beta2)
        m_b1_hat = self.m_b1 / (1 - self.beta1)
        v_b1_hat = self.v_b1 / (1 - self.beta2)

        m_W2_hat = self.m_W2 / (1 - self.beta1)
        v_W2_hat = self.v_W2 / (1 - self.beta2)
        m_b2_hat = self.m_b2 / (1 - self.beta1)
        v_b2_hat = self.v_b2 / (1 - self.beta2)

        self.W1 -= self.learning_rate * m_W1_hat / (np.sqrt(v_W1_hat) + self.epsilon)
        self.b1 -= self.learning_rate * m_b1_hat / (np.sqrt(v_b1_hat) + self.epsilon)
        self.W2 -= self.learning_rate * m_W2_hat / (np.sqrt(v_W2_hat) + self.epsilon)
        self.b2 -= self.learning_rate * m_b2_hat / (np.sqrt(v_b2_hat) + self.epsilon)

    def train(self, X, y, X_test, y_test, stop_losses, epochs=1000):
        epoch = 0
        while epoch <= epochs:
            output = self.forward(X)
            self.backward(X, y, output)

            self.loss = np.mean((output - y) ** 2)
            test_loss = np.mean((self.forward(X_test) - y_test) ** 2)

            # Запись ошибок для графика
            self.train_losses.append(self.loss)
            self.test_losses.append(test_loss)

            if epoch % 10000 == 0:
                print(f"Эпоха {epoch}, Ошибка на обучении: {self.loss}, Ошибка на тесте: {test_loss}")

            if self.loss < stop_losses:
                print(f"Целевая точность достигнута на эпохе {epoch}")
                break

            epoch += 1

    def save_weights(self, filename="weights_update.npz"):
        np.savez(filename, W1=self.W1, b1=self.b1, W2=self.W2, b2=self.b2)
        print(f"Веса сохранены в {filename}")

    def load_weights(self, filename="weights_update.npz"):
        data = np.load(filename)
        self.W1 = data['W1']
        self.b1 = data['b1']
        self.W2 = data['W2']
        self.b2 = data['b2']
        print(f"Веса загружены из {filename}")

    def predict(self, X):
        return self.forward(X)


# Основная часть для тренировки обеих моделей
stop_losses = 5e-3

# Обучаем модель с дефолтными параметрами
model_default = Perceptron_default(X_train.shape[1], 10, 1, 0.01)
model_default.train(X_train, y_train, X_test, y_test, stop_losses)

# Обучаем модель с обновлениями
model_update = Perceptron_update(X_train.shape[1], 10, 1, 0.01, epochs=3000000)
model_update.train(X_train, y_train, X_test, y_test, stop_losses)

# Графики
plt.figure(figsize=(10, 8))

# 1. Лосс первой модели на трейне
plt.subplot(2, 2, 1)
plt.plot(model_default.train_losses, label='Train Loss (default)')
plt.legend()
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.title('Train Loss (default)')

# 2. Лосс второй модели на трейне
plt.subplot(2, 2, 2)
plt.plot(model_update.train_losses, label='Train Loss (update)')
plt.legend()
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.title('Train Loss (update)')

# 3. Лосс первой модели на трейне и тесте
plt.subplot(2, 2, 3)
plt.plot(model_default.train_losses, label='Train Loss (default)')
plt.plot(model_default.test_losses, label='Test Loss (default)')
plt.legend()
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.title('Train and Test Loss (default)')

# 4. Лосс второй модели на трейне и тесте
plt.subplot(2, 2, 4)
plt.plot(model_update.train_losses, label='Train Loss (update)')
plt.plot(model_update.test_losses, label='Test Loss (update)')
plt.legend()
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.title('Train and Test Loss (update)')

plt.tight_layout()
plt.show()
