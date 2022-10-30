import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {

    static boolean DEBUG = false;
    public static void main(String[] args) {

        MyAVLtree avlTree = new MyAVLtree();

        try {
            File myObj = new File("file.txt");
            Scanner myReader = new Scanner(myObj);
            int i = 1;
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                String[] words = data.split(" ");
                String cmd = words[0];
                int number = Integer.parseInt(words[1]);

                switch (cmd) {
                    case "I": {
                        if(DEBUG)
                        System.out.println("Line " + i + ": " + cmd + " " + number);
                        avlTree.insert(number);
                        avlTree.printTree();
                        System.out.println();
                        break;
                    }
                    case "F": {
                        if(DEBUG)
                        System.out.println("Line " + i + ": " + cmd + " " + number);
                        avlTree.searchItem(number);
                        break;
                    }

                    case "D": {
                        if(DEBUG)
                        System.out.println("Line " + i + ": " + cmd + " " + number);
                        avlTree.deleteItem(number);
                        avlTree.printTree();
                        System.out.println();
                        break;
                    }

                    default: {
                        System.out.println("Invalid Input");
                        return;
                    }

                }

                i++;
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
            e.printStackTrace();
        }


    }


}
