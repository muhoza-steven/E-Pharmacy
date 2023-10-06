package main;

import java.io.*;
import java.time.LocalDate;
import java.util.ArrayList;

import org.json.simple.parser.ParseException;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public class PrescriptionManagement {
    public static void main(String[] args) throws IOException, ParseException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String productsFilePath = "data/products.json";
        String prescriptionsFilePath = "data/prescriptions.json";
        FileHandler fileHandler = new FileHandler();

        while (true) {
            System.out.println("Choose an option");
            System.out.println("1. Add a prescription");
            System.out.println("2. View prescriptions");
            System.out.println("3. Delete prescriptions");
            System.out.println("4. Exit");
            System.out.print("Enter your choice: ");
            String line = reader.readLine();
            int choice;

            try {
                choice = Integer.parseInt(line);
            } catch (NumberFormatException e) {
                System.out.println("Only integers allowed");
                continue;
            }

            switch (choice) {
                case 1:
                    PrescriptionManagement.addPrescription(reader, fileHandler, productsFilePath, prescriptionsFilePath);
                    break;
                case 2:
                    PrescriptionManagement.viewPrescriptions(prescriptionsFilePath);
                    break;
                case 3:
                    System.out.print("Enter prescription ID to delete: ");
                    Prescription.deletePrescription(prescriptionsFilePath, reader.readLine());
                    break;
                case 4:
                    System.out.println("Exiting the Prescription Management section...");
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void addPrescription(BufferedReader reader, FileHandler fileHandler, String productsFilePath, String prescriptionsFilePath) throws IOException, ParseException {
        Prescription prescription = new Prescription();

        System.out.print("Enter prescription ID: ");
        prescription.setPrescriptionID(reader.readLine());

        System.out.print("Enter customer ID: ");
        prescription.setCustomerID(reader.readLine());

        System.out.print("Enter doctor's name: ");
        prescription.setDoctorName(reader.readLine());

        prescription.setDate(LocalDate.now());

        int numMedications = -1;
        while (numMedications == -1) {
            try {
                System.out.print("Enter the number of medications to add: ");
                numMedications = Integer.parseInt(reader.readLine());
            } catch (NumberFormatException e) {
                System.out.println("Only integers allowed");
            }
        }

        ArrayList<Medication> medications = new ArrayList<>();
        JSONArray availableMedications = fileHandler.readJSONArrayFromFile(productsFilePath);

        System.out.println("--------------------------------------------------------------------------------");
        System.out.println("|");
        System.out.println("|\t\t\t\t Available Medications");
        System.out.println("|");
        System.out.println("--------------------------------------------------------------------------------");
        System.out.println("| Medication ID | Medication Name | Medication Price | Medication Quantity |");
        System.out.println("--------------------------------------------------------------------------------");

        for (Object obj : availableMedications) {
            JSONObject jsonObject = (JSONObject) obj;
            String medicationId_ = (String) jsonObject.get("code");
            String medicationName_ = (String) jsonObject.get("name");
            String medicationPrice_ = (String) jsonObject.get("price");
            String medicationQuantity_ = (String) jsonObject.get("quantity");

            System.out.println("|"
                    + PrescriptionManagement.fillString(medicationId_, 15) + " "
                    + PrescriptionManagement.fillString(medicationName_, 17) + " "
                    + PrescriptionManagement.fillString(medicationPrice_, 18) + " "
                    + PrescriptionManagement.fillString(medicationQuantity_, 21)
            );
        }

        System.out.println("--------------------------------------------------------------------------------");

        for (int i = 1; i <= numMedications; i++) {
            System.out.print("Enter details for medication " + i + ":");

            System.out.print("ID: ");
            String id_ = reader.readLine();

            System.out.print("Name: ");
            String name_ = reader.readLine();

            System.out.print("Details: ");
            String details_ = reader.readLine();

            System.out.print("Dosage: ");
            String dosage_ = reader.readLine();

            int quantity_ = -1;
            while (quantity_ == -1) {
                try {
                    System.out.print("Quantity: ");
                    quantity_ = Integer.parseInt(reader.readLine());
                } catch (NumberFormatException e) {
                    System.out.println("Only integers allowed");
                }
            }

            medications.add(new Medication(id_, name_, details_, dosage_, quantity_));
        }

        prescription.setMedications(medications);
        prescription.addPrescription(prescriptionsFilePath);
    }

    private static void viewPrescriptions(String prescriptionsFilePath) throws ParseException {
        ArrayList<Prescription> prescriptions = Prescription.viewPrescription(prescriptionsFilePath);

        if (prescriptions.isEmpty()) {
            System.out.println("No prescriptions available\n");
        } else {
            System.out.println("| PrescriptionID |   DoctorName   |   CustomerID   |   Date   |");
            System.out.println("***************************************************************");

            for (Prescription p : prescriptions) {
                System.out.println("|" + PrescriptionManagement.fillString(p.getPrescriptionID(), 16)
                        + "|" + PrescriptionManagement.fillString(p.getDoctorName(), 16)
                        + "|" + PrescriptionManagement.fillString(p.getCustomerID(), 16)
                        + "|" + PrescriptionManagement.fillString(p.getDate().toString(), 10)
                        + "|"
                );

                System.out.println();
                System.out.println("| MedicationID |   Name   |  Quantity  |");
                for (Medication med : p.getMedications()) {
                    System.out.println("|" + PrescriptionManagement.fillString(med.getID(), 14)
                            + "|" + PrescriptionManagement.fillString(med.getName(), 10)
                            + "|" + PrescriptionManagement.fillString("" + med.getQuantity(), 12)
                            + "|"
                    );
                }

                System.out.print("\n");
                System.out.println("***************************************************************");
            }

            System.out.println();
        }
    }

    private static String fillString(String s, int capacity) {
        int length = s.length();
        StringBuilder result = new StringBuilder(s);

        while (length < capacity) {
            result.append(" ");
            length += 1;
        }

        return result.toString();
    }
}
