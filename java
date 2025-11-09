import java.util.Scanner;

public class HammingCode {

    // Function to generate Hamming Code (7,4)
    public static void generateHammingCode(int[] data, int[] hamming) {
        // Data bits at their positions
        hamming[2] = data[0]; // d1 at position 3
        hamming[4] = data[1]; // d2 at position 5
        hamming[5] = data[2]; // d3 at position 6
        hamming[6] = data[3]; // d4 at position 7

        // Calculate parity bits (even parity)
        hamming[0] = hamming[2] ^ hamming[4] ^ hamming[6]; // p1
        hamming[1] = hamming[2] ^ hamming[5] ^ hamming[6]; // p2
        hamming[3] = hamming[4] ^ hamming[5] ^ hamming[6]; // p4
    }

    // Function to detect the position of a single-bit error
    public static int detectError(int[] hamming) {
        int p1 = hamming[0] ^ hamming[2] ^ hamming[4] ^ hamming[6];
        int p2 = hamming[1] ^ hamming[2] ^ hamming[5] ^ hamming[6];
        int p4 = hamming[3] ^ hamming[4] ^ hamming[5] ^ hamming[6];

        int errorPos = p4 * 4 + p2 * 2 + p1 * 1;
        return errorPos;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] data = new int[4];
        int[] hamming = new int[7];

        // Input 4 data bits
        System.out.println("Enter 4 data bits (0 or 1): ");
        for (int i = 0; i < 4; i++) {
            data[i] = scanner.nextInt();
        }

        // Generate the Hamming code
        generateHammingCode(data, hamming);

        // Print the generated Hamming Code (7 bits)
        System.out.print("\nGenerated Hamming Code (7 bits): ");
        for (int i = 0; i < 7; i++) {
            System.out.print(hamming[i] + " ");
        }
        System.out.println();

        // Ask the user if they want to simulate an error
        System.out.print("\nDo you want to simulate an error? (y/n): ");
        char simulate = scanner.next().charAt(0);

        if (simulate == 'y' || simulate == 'Y') {
            System.out.print("Enter bit position to flip (1 to 7): ");
            int pos = scanner.nextInt();

            if (pos >= 1 && pos <= 7) {
                hamming[pos - 1] ^= 1; // Flip the bit

                // Print the Hamming Code after introducing the error
                System.out.print("Hamming Code after error: ");
                for (int i = 0; i < 7; i++) {
                    System.out.print(hamming[i] + " ");
                }
                System.out.println();

                // Detect error position
                int errorPos = detectError(hamming);
                if (errorPos == 0) {
                    System.out.println("No error detected.");
                } else {
                    System.out.println("Error detected at position: " + errorPos);
                    hamming[errorPos - 1] ^= 1; // Correct the bit

                    // Print the corrected Hamming Code
                    System.out.print("Corrected Hamming Code: ");
                    for (int i = 0; i < 7; i++) {
                        System.out.print(hamming[i] + " ");
                    }
                    System.out.println();
                }
            } else {
                System.out.println("Invalid position!");
            }
        }

        scanner.close();
    }
}
