// Tiny file-loading helper stub for the OOP implementation.
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileLoaderStub {
    public static String readFile(String path) throws Exception {
        try {
        return new String(Files.readAllBytes(Paths.get(path)));
        } catch (Exception e){
            throw new RuntimeException("Could not open file: " + path);
        }
    }
}
