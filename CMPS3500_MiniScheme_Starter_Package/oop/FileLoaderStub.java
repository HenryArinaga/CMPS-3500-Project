// Tiny file-loading helper stub for the OOP implementation.
import java.nio.file.Files;
import java.nio.file.Path;

public class FileLoaderStub {
    public static String readFile(String path) throws Exception {
        try {
        return Files.readString(Path.of(path));
        } catch (Exception e){
            throw new RuntimeException("Could not open file: " + path);
        }
    }
}
