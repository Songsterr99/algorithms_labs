import java.util.*;
import java.io.*;

public class cards {
    private static int[] numbers;
    private static int n = 0;
    public static void main(String[] args) {
        try{
            readFile();
            int answer = analyzeData();
            writeFile(answer);
        }
        catch(Exception e){
            System.out.println(e.getMessage());
        }

    }

    private static void readFile() throws FileNotFoundException{
        File file = new File("input.txt");
        Scanner scanner = new Scanner(file);
        String size = scanner.nextLine();
        n = Integer.parseInt(size);
        numbers = new int[n];
        String line = scanner.nextLine();
        String[] numbersString = line.split(" ");
        int a = 1;
        for(String numb: numbersString){
            numbers[Integer.parseInt(numb) - 1] = a;
            ++a;
        }
        scanner.close();
    }

    private static int analyzeData(){
        int[][] dataTable = new int[n][n];
        for(int l = 1; l < n; l++){
            for(int j = l, i = 0; j < n; j++, i++){
                dataTable[i][j] = n * n;
                for(int k = i; k < j; k++){
                    int way = dataTable[i][k] + dataTable[k + 1][j] + Math.abs(numbers[j] - numbers[k]);
                    if(way < dataTable[i][j])
                        dataTable[i][j] = way;
                }
            }
        }
        return dataTable[0][n - 1];
    }
    private static void writeFile(int answer) throws FileNotFoundException {
        File file = new File("output.txt");
        PrintWriter pw = new PrintWriter(file);
        pw.println(answer);
        pw.close();
    }

}
