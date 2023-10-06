package main;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Objects;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.ParseException;

public class Prescription {
    private String prescriptionID;
    private String customerID;
    private String doctorName;
    private ArrayList<Medication> medications;
    private LocalDate date;
    private JSONArray prescriptionList;

    public Prescription() {
        prescriptionList = new JSONArray();
    }

    public Prescription(String _prescriptionID, String _customerID, String _doctorName, ArrayList<Medication> _medication) {
        prescriptionID = _prescriptionID;
        customerID = _customerID;
        doctorName = _doctorName;
        medications = _medication;
        date = LocalDate.now();
    }

    public Prescription(String prescriptionID, String customerID, String doctorName, LocalDate date, ArrayList<Medication> medications) {
        this.prescriptionID = prescriptionID;
        this.customerID = customerID;
        this.doctorName = doctorName;
        this.medications = medications;
        this.date = date;
    }

    public void setPrescriptionID(String prescriptionID) {
        this.prescriptionID = prescriptionID;
    }

    public void setCustomerID(String customerID) {
        this.customerID = customerID;
    }

    public void setDoctorName(String doctorName) {
        this.doctorName = doctorName;
    }

    public void setMedications(ArrayList<Medication> medications) {
        this.medications = medications;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public void setPrescriptionList(JSONArray prescriptionList) {
        this.prescriptionList = prescriptionList;
    }

    public String getPrescriptionID() {
        return this.prescriptionID;
    }

    public String getCustomerID() {
        return this.customerID;
    }

    public String getDoctorName() {
        return this.doctorName;
    }

    public ArrayList<Medication> getMedications() {
        return this.medications;
    }

    public LocalDate getDate() {
        return this.date;
    }

    public JSONArray getPrescriptionList() {
        return this.prescriptionList;
    }

    public void addPrescription(String filePath) throws ParseException {
        // Format for the prescription: {"DoctorName":"Yves","PrescriptionID":"TA3","Medications":[{"quantity":2,"processedStatus":false,"name":"IBUPROFEN","id":"IB7"}],"CustomerID":"GR","Date":"2023-08-07"}
        FileHandler fileHandler = new FileHandler();
        JSONArray existingPrescriptions = fileHandler.readJSONArrayFromFile(filePath);
        JSONObject jsonObject = new JSONObject();

        jsonObject.put("DoctorName", doctorName);
        jsonObject.put("PrescriptionID", prescriptionID);
        jsonObject.put("Medications", getMedicationsOnPrescription());
        jsonObject.put("CustomerID", customerID);
        jsonObject.put("Date", date.toString());

        existingPrescriptions.add(jsonObject);
        fileHandler.writeJSONArrayToFile(existingPrescriptions, filePath);
    }

    private JSONArray getMedicationsOnPrescription() {
        JSONArray jsonArray = new JSONArray();

        for (Medication medication : medications) {
            JSONObject jsonObject = new JSONObject();
            jsonObject.put("quantity", medication.getQuantity());
            jsonObject.put("processedStatus", medication.getProcessedStatus());
            jsonObject.put("name", medication.getName());
            jsonObject.put("id", medication.getID());
            jsonArray.add(jsonObject);
        }

        return jsonArray;
    }

    public static ArrayList<Prescription> viewPrescription(String filePath) throws ParseException {
        FileHandler fileHandler = new FileHandler();
        JSONArray jsonArray = fileHandler.readJSONArrayFromFile(filePath);
        ArrayList<Prescription> prescriptions = new ArrayList<>();

        for (Object obj : jsonArray) {
            JSONObject jsonObject = (JSONObject) obj;

            String doctorName = (String) jsonObject.get("DoctorName");
            String prescriptionID = (String) jsonObject.get("PrescriptionID");
            String customerID = (String) jsonObject.get("CustomerID");
            String date = (String) jsonObject.get("Date");
            LocalDate dateToPrint = LocalDate.parse(date);

            ArrayList<Medication> medications = new ArrayList<>();
            JSONArray medicationsArray = (JSONArray) jsonObject.get("Medications");

            for (Object medObj : medicationsArray) {
                JSONObject medication = (JSONObject) medObj;
                String medicationID = (String) medication.get("id");
                String medicationName = (String) medication.get("name");
                int quantity = Integer.parseInt("" + medication.get("quantity"));

                medications.add(new Medication(medicationID, medicationName, quantity));
            }

            prescriptions.add(new Prescription(prescriptionID, customerID, doctorName, dateToPrint, medications));
        }

        return prescriptions;
    }

    public static void deletePrescription(String filePath, String idToDelete) throws ParseException {
        FileHandler fileHandler = new FileHandler();
        JSONArray existingPrescriptions = fileHandler.readJSONArrayFromFile(filePath);
        int indexToDelete = -1;

        for (int i = 0; i < existingPrescriptions.size(); i++) {
            JSONObject jsonObject = (JSONObject) existingPrescriptions.get(i);
            String existingPrescriptionID = (String) jsonObject.get("PrescriptionID");

            if (Objects.equals(idToDelete, existingPrescriptionID)) {
                indexToDelete = i;
                break;
            }
        }

        if (indexToDelete != -1) {
            existingPrescriptions.remove(indexToDelete);
            fileHandler.writeJSONArrayToFile(existingPrescriptions, filePath);
        }
    }
}
