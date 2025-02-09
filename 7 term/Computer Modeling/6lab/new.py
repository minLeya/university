import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler

# Загрузка данных через pandas
file_path = '1.xls'
data_frame = pd.read_excel(file_path)

# Разделение на признаки (X) и целевую переменную (y)
features = data_frame.drop(['Cредний доход на одно домохозяйство', 'Район'], axis=1)
target = data_frame['Cредний доход на одно домохозяйство'].values.reshape(-1, 1)

# Нормализация данных с использованием StandardScaler
scaler_features = StandardScaler()
scaler_target = StandardScaler()

features_normalized = scaler_features.fit_transform(features)
target_normalized = scaler_target.fit_transform(target)

# Разделение на обучающую и тестовую выборки
np.random.seed(42)
indices = np.arange(len(data_frame))
np.random.shuffle(indices)
split_index = int(0.75 * len(data_frame))

train_indices = indices[:split_index]
test_indices = indices[split_index:]

features_train, features_test = features_normalized[train_indices], features_normalized[test_indices]
target_train, target_test = target_normalized[train_indices], target_normalized[test_indices]

# Определение класса Перцептрон
class PerceptronModel:
    def __init__(self, input_dim, hidden_dim, output_dim, learning_rate=0.01):
        self.weights_hidden = np.random.randn(input_dim, hidden_dim) * 0.1
        self.bias_hidden = np.zeros((1, hidden_dim))
        self.weights_output = np.random.randn(hidden_dim, output_dim) * 0.1
        self.bias_output = np.zeros((1, output_dim))
        self.learning_rate = learning_rate
        self.loss = 1
        self.train_loss_history = []
        self.test_loss_history = []

    def sigmoid(self, z):
        return 1 / (1 + np.exp(-np.clip(z, -500, 500)))

    def sigmoid_derivative(self, z):
        return z * (1 - z)

    def forward(self, features):
        self.hidden_layer_input = np.dot(features, self.weights_hidden) + self.bias_hidden
        self.hidden_layer_output = self.sigmoid(self.hidden_layer_input)
        self.output_layer_input = np.dot(self.hidden_layer_output, self.weights_output) + self.bias_output
        self.output_layer_output = self.output_layer_input  # Линейный выход для регрессии
        return self.output_layer_output

    def backward(self, features, target, predictions):
        num_samples = features.shape[0]
        error = predictions - target

        # Градиенты для выходного слоя
        d_output_layer = error
        grad_weights_output = np.dot(self.hidden_layer_output.T, d_output_layer) / num_samples
        grad_bias_output = np.sum(d_output_layer, axis=0, keepdims=True) / num_samples

        # Градиенты для скрытого слоя
        d_hidden_layer = np.dot(d_output_layer, self.weights_output.T) * self.sigmoid_derivative(self.hidden_layer_output)
        grad_weights_hidden = np.dot(features.T, d_hidden_layer) / num_samples
        grad_bias_hidden = np.sum(d_hidden_layer, axis=0, keepdims=True) / num_samples

        # Обновление весов и смещений
        self.weights_output -= self.learning_rate * grad_weights_output
        self.bias_output -= self.learning_rate * grad_bias_output
        self.weights_hidden -= self.learning_rate * grad_weights_hidden
        self.bias_hidden -= self.learning_rate * grad_bias_hidden

    def train(self, features_train, target_train, features_test, target_test, loss_threshold, max_epochs=100000):
        epoch = 0
        while True:
                predictions = self.forward(features_train)
                self.backward(features_train, target_train, predictions)

                train_loss = np.mean((predictions - target_train) ** 2)
                test_loss = np.mean((self.forward(features_test) - target_test) ** 2)

                self.train_loss_history.append(train_loss)
                self.test_loss_history.append(test_loss)

                if epoch % 10000 == 0:
                    print(f"Epoch {epoch}: Train Loss = {train_loss}, Test Loss = {test_loss}")

                # Условие завершения
                if train_loss < loss_threshold:
                    print(f"Training completed at epoch {epoch} with Train Loss = {train_loss}")
                    break

                epoch += 1

    def predict(self, features):
        return self.forward(features)


# Основная часть: обучение модели
loss_threshold = 0.0048
perceptron = PerceptronModel(input_dim=features_train.shape[1], hidden_dim=10, output_dim=1, learning_rate=0.01)
perceptron.train(features_train, target_train, features_test, target_test, loss_threshold)

# Графики
plt.figure(figsize=(10, 6))

# График ошибки на обучении
plt.plot(perceptron.train_loss_history, label='Train Loss')
plt.plot(perceptron.test_loss_history, label='Test Loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.title('Train and Test Loss')
plt.legend()
plt.show()
