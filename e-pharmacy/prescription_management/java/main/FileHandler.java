package main;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import org.json.simple.JSONArray;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class FileHandler {
    public JSONArray readJSONArrayFromFile(String filePath) throws ParseException {
        try (FileReader fileReader = new FileReader(filePath)) {
            if (fileReader.read() == -1) {
                return new JSONArray();
            } else {
                fileReader.close();
                return (JSONArray) new JSONParser().parse(new FileReader(filePath));
            }
        } catch (IOException e) {
            return new JSONArray();
        }
    }

    public void writeJSONArrayToFile(JSONArray jsonArray, String filePath) {
        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(jsonArray.toJSONString());
            fileWriter.flush();
            System.out.println("Data written to " + filePath + " successfully!");
        } catch (IOException e) {
            System.out.println("Error while writing data to file: " + e.getMessage());
        }
    }
}
