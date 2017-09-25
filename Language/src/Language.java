import java.io.*;
import java.util.*;

public class Language {
    private static Elements []firLang;
    private static int []secLang;
    private static int []commonWords;
    private static int []sequence;

    private static int size = 0;
    private static int seqSize = 0;
    private static int firSize = 0;
    private static int secSize= 0;
    public static void main(String[] args) {
        try {
            readFile();
            Arrays.sort(firLang);
            findCommonWords();
            analyzeCommonWords();
            writeFile();
        }
        catch(Exception e){
            System.out.println(e.getMessage());
        }
    }
    private static void readFile() throws FileNotFoundException {
        File file = new File("input.txt");
        Scanner scanner = new Scanner(file);
        String langSizes = scanner.nextLine();
        String[] lSizes = langSizes.split(" ");

        readFirLang(Integer.parseInt(lSizes[0]), scanner.nextLine());
        readSecLang(Integer.parseInt(lSizes[1]), scanner.nextLine());
        scanner.close();
    }

    private static void writeFile() throws FileNotFoundException{
        File file = new File("output.txt");
        PrintWriter pw = new PrintWriter(file);
        pw.println(seqSize);
        pw.close();
    }

    private static void readFirLang(int size, String line){
        firSize = size;
        firLang = new Elements[firSize];
        String[] numbers = line.split(" ");
        int i = 0;
        for(String numb : numbers){
            firLang[i] = new Elements(i, Integer.parseInt(numb));
            ++i;
        }
    }

    private static void readSecLang(int size, String line){
        secSize = size;
        secLang = new int[secSize];
        String[] numbers = line.split(" ");
        int i = 0;
        for(String numb : numbers){
            secLang[i] = Integer.parseInt(numb);
            ++i;
        }
    }

    private static void analyzeCommonWords(){
        if(size == 0)
            return;
        sequence = new int[size];
        sequence[0] = commonWords[0];
        ++seqSize;
        for(int i = 1; i < size; i++){
            analyzeWords(commonWords[i],0, seqSize );
        }
    }

    private static boolean analyzeWords(int key, int left, int right){
        int mid = left + (right - left) / 2;
        if(left == right && right == seqSize){
            ++seqSize;
            sequence[left] = key;
            return true;
        } else if(left == right) {
            sequence[left] = key;
            return true;
        }
        if(sequence[mid] > key){
            return analyzeWords(key, left, mid);
        } else{
            return  analyzeWords(key, mid + 1, right);
        }

    }

    private static void findCommonWords(){
        commonWords = new int[secSize];
        int amount = 0;
        for(int i = 0; i < secSize; i++){
            Elements helpElement = searchCommonWords(secLang[i], 0, firSize);
            if(helpElement != null){
                commonWords[amount] = helpElement.order;
                ++amount;
            }
        }
        size = amount;
    }

    public static Elements searchCommonWords(int key, int left, int right){
        int mid = left + (right - left) / 2;
        if(left >= right)
            return null;

        if(firLang[mid].value == key){
            return firLang[mid];
        } else if(firLang[mid].value > key){
            return searchCommonWords(key, left, mid);
        } else{
            return  searchCommonWords(key, mid + 1, right);
        }

    }

}

class Elements implements Comparable<Elements>
{
    public int order;
    public int value;
    public Elements(int order, int value){
        this.order = order;
        this.value = value;
    }

    @Override
    public int compareTo(Elements el) {
        if(this.value < el.value){
            return -1;
        } else if(this.value > el.value) {
            return 1;
        }
        return 0;
    }
}