import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Day3 {

    public static void main(String[] args) {
        try {
            IntersectionFinder temp = new IntersectionFinder("./Day3Data.txt");
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public static class IntersectionFinder {

        private ArrayList<LineDay3> tempLines;

        public IntersectionFinder(String fileName) throws IOException {
            BufferedReader reader = new BufferedReader(new FileReader(fileName));
            String st;
            st = reader.readLine();
            String temp[] = st.split(",");
            for (String i: temp) {
                if (tempLines.size() == 0) {
                    tempLines.add(new LineDay3(i));
                } else {
                    LineDay3 tempLine = tempLines.get(tempLines.size()-1);
                    tempLines.add(new LineDay3(i, tempLine));
                }
            }
            st = reader.readLine();
            // TODO fix the next part
            int y = -1;
            int x = -1;
            for (String i : temp) {

                LineDay3 tempLine = tempLines.get(tempLines.size() - 1);
                for (LineDay3 subLine: tempLines) {
                    if (subline.intersects(tempLine)){ 

                    }
                }    
            }
            

        }


        private class LineDay3 {
            public int x, y, length;
            boolean vertical;

            public LineDay3(String lines, LineDay3 lastLine) {
                LineDay3Local(lastLine);
                parseString(lines);
            }
            public LineDay3(String lines) {
                parseString(lines);
            }
            private void LineDay3Local(LineDay3 lastLine) {
                x = lastLine.x;
                y = lastLine.y;
                if (vertical) {
                    y = y + length;
                } else {
                    x = x + length;
                }
            }



            private void parseString(String line) {
                String tempLine[] = line.split(".");
                vertical = tempLine[0].equals('D') || tempLine[0].equals('U');
                length = Integer.parseInt(line.substring(1));
                if (vertical) {
                    if (tempLine[0].equals('D')) {
                        y = y - length;
                    }
                } else {
                    if (tempLine[0].equals('L')) {
                        x = x - length;
                    }
                }
            }

            public boolean intersects(LineDay3 line) {
                if (vertical) {
                    return (line.x >= y && line.x <= y+length) && (line.x >= y && line.x <= y+length);
                } else {
                    return (line.x >= y && line.x <= y+length) && (line.x >= y && line.x <= y+length);
                }
            }
        }
    }
}