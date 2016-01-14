import java.util.Scanner;


public class RandomProgram {
    static String program = "";
    static int numTabs = 0;
    public static void main(String[] args) {


        add_to_program(import_statements());
        add_to_program(class_statement());
        add_to_program(class_variables());
        add_to_program(main_header());
        add_to_program(create_program());
        add_to_program(end_main_header());
        add_to_program(end_class_statement());

        System.out.println(program);
    }

    static void add_to_program(Line line) {
        String new_line = "";
        if(line.increaseTabs < 0)
            numTabs += line.increaseTabs;
        for(int i = 0; i < numTabs; i++) {
            new_line += "\t";
        }
        program += (new_line + line.line + "\n");
        if(line.increaseTabs > 0)
            numTabs += line.increaseTabs;
    }

    static Line import_statements() {
        return new Line("", 0); // stub
    }
    static Line class_statement() {
        return new Line("public class RandomQuote {", 1);
    }
    static Line class_variables() {
        return new Line("int pointless_variable = 0;", 0);
    }
    static Line main_header() {
        return new Line("public static void main(String[] args) {", 1);
    }
    static Line create_program() {
        Scanner scan = new Scanner(System.in);
        String line = scan.nextLine();
        return new Line("System.out.println(\"" + line + "\");", 0);
    }
    static Line end_main_header() {
        return new Line("}", -1);
    }
    static Line end_class_statement() {
        return new Line("}", -1);
    }

    public static class Line {
        String line;
        int increaseTabs;
        public Line(String line, int increaseTabs) {
            this.line = line;
            this.increaseTabs = increaseTabs;
        }
    }


}
