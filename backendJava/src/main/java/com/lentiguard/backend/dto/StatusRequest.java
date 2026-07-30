package com.lentiguard.backend.dto;

public class StatusRequest {

    private int deviceId;
    private boolean lidOpen;
    private boolean lensCasePresent;
    private boolean alarmActive;
    private boolean wifiConnected;
    private int batteryLevel;

    public StatusRequest(int deviceId, boolean lidOpen, boolean lensCasePresent, boolean alarmActive, boolean wifiConnected, int batteryLevel) {
        this.deviceId = deviceId;
        this.lidOpen = lidOpen;
        this.lensCasePresent = lensCasePresent;
        this.alarmActive = alarmActive;
        this.wifiConnected = wifiConnected;
        this.batteryLevel = batteryLevel;
    }

    public int getDeviceId() {
        return deviceId;
    }

    public boolean isLidOpen() {
        return lidOpen;
    }

    public boolean isLensCasePresent() {
        return lensCasePresent;
    }

    public boolean isAlarmActive() {
        return alarmActive;
    }

    public boolean isWifiConnected() {
        return wifiConnected;
    }

    public int getBatteryLevel() {
        return batteryLevel;
    }

    public void setDeviceId(int deviceId) {
        this.deviceId = deviceId;
    }

    public void setLidOpen(boolean lidOpen) {
        this.lidOpen = lidOpen;
    }

    public void setLensCasePresent(boolean lensCasePresent) {
        this.lensCasePresent = lensCasePresent;
    }

    public void setAlarmActive(boolean alarmActive) {
        this.alarmActive = alarmActive;
    }

    public void setWifiConnected(boolean wifiConnected) {
        this.wifiConnected = wifiConnected;
    }

    public void setBatteryLevel(int batteryLevel) {
        this.batteryLevel = batteryLevel;
    }
}
