import java.io.*;
import java.net.*;
import java.util.Scanner;

public class TCPClient implements Runnable {
    private String name = null;
    private String host = null;
    private int serverPort = 0;

    private String journalFileName = null;
    
    public TCPClient(String clientName, String hostName, int port, String fileName) {
        name = clientName;
        host = hostName;
        serverPort = port;
        journalFileName = fileName;
    }

    public void run() {
        writeToJournal("Client is running...");
        try {
            Socket socket = new Socket(host, serverPort);
            PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            writeToJournal("Client connected to server: " + host + ":" + serverPort);

            Scanner scanner = new Scanner(System.in);
            String argument = "";
            while (!argument.endsWith("="))
            {
                System.out.print("Enter argument: ");
                argument = scanner.nextLine();
                writeToJournal("Writing string to server: " + argument);
                writer.println(argument);
                writer.flush();
            }

            writeToJournal("Finished writing expression to server");

            String result = reader.readLine();
            writeToJournal("Result returned from server: " + result + "\n");

            writer.close();
            reader.close();
            socket.close();

            Thread.yield();
        } catch (UnknownHostException e) {
            System.err.println("Exception: " + e.toString());
        } catch (IOException e) {
            System.err.println("Exception: " + e.toString());
        }
    }

    public void writeToJournal(String entry) {
        try (FileWriter writer = new FileWriter(journalFileName, true)) {
            writer.write(entry + "\n");
        } catch (IOException e) {
            System.err.println("Error occurred while writing to the server journal: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        try {
            File file = new File("settings.txt");
            Scanner scanner = new Scanner(file);
            String host = scanner.nextLine();
            int serverPort = Integer.parseInt(scanner.nextLine());
            String journalFileName = scanner.nextLine();
            scanner.close();

            String name = "client";
            TCPClient client = new TCPClient(name, host, serverPort, journalFileName);
            Thread clientThread = new Thread(client);
            clientThread.start();
        } catch (FileNotFoundException e) {
            System.err.println("Error: settings.txt file not found.");
            e.printStackTrace();
        } catch (NumberFormatException e) {
            System.err.println("Error: Invalid port number in settings.txt");
            e.printStackTrace();
        }
    }
}
