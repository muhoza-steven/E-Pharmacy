package main;

public class Medication {
    private String ID;
    private String name;
    private String details;
    private String dosage;
    private int quantity;
    private Boolean processedStatus;

    public Medication() {
        this.processedStatus = false;
    }

    public Medication(String _id, String _name, int qty) {
        this.ID = _id;
        this.name = _name;
        this.quantity = qty;
        this.processedStatus = false;
    }

    public Medication(String id, String name, String details, String dosage, int quantity) {
        this.ID = id;
        this.name = name;
        this.details = details;
        this.dosage = dosage;
        this.quantity = quantity;
        this.processedStatus = false;
    }

    public void setID(String id) {
        this.ID = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setDetails(String details) {
        this.details = details;
    }

    public void setDosage(String dosage) {
        this.dosage = dosage;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public void setProcessedStatus(boolean processedStatus) {
        this.processedStatus = processedStatus;
    }

    public String getID() {
        return this.ID;
    }

    public String getName() {
        return this.name;
    }

    public String getDetails() {
        return this.details;
    }

    public String getDosage() {
        return this.dosage;
    }

    public int getQuantity() {
        return this.quantity;
    }

    public boolean getProcessedStatus() {
        return this.processedStatus;
    }

    public String toString() {
        return this.ID + "," + this.name + "," + this.quantity + "," + this.processedStatus;
    }
}
