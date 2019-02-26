/*
 * Compile and run this code. Then look at the file
 * descriptors. Notice you get extra ones when you open other I/O channels
 * besides the standard stdin/stdout/stderr.
 *
 * /opt/android-studio/jre/bin/javac FileIO.java 
 * /opt/android-studio/jre/bin/java FileIO 
 * ls -l /proc/$(pidof java)/fd
 */
import java.io.*;

public class FileIO {
    public static void main( String args[] ) throws IOException {
        FileOutputStream out = null;
        try {
            out = new FileOutputStream("output.txt");
            while( true ) {
            }
        } finally {
            if ( out != null ) {
                out.close();
            }
        }
    }
}

