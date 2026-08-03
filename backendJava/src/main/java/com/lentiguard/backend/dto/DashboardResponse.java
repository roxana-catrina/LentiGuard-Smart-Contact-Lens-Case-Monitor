package com.lentiguard.backend.dto;

import com.lentiguard.backend.entity.Event;

import java.util.List;

public class DashboardResponse {

    private String deviceName;

    private String serialNumber;

    private boolean lidOpen;

    private boolean lensCasePresent;

    private boolean alarmActive;

    private boolean wifiConnected;

    private Integer batteryLevel;

    private List<Event> lastEvents;

    public DashboardResponse() {
    }

    public String getDeviceName() {
        return deviceName;
    }

    public void setDeviceName(String deviceName) {
        this.deviceName = deviceName;
    }

    public String getSerialNumber() {
        return serialNumber;
    }

    public void setSerialNumber(String serialNumber) {
        this.serialNumber = serialNumber;
    }

    public boolean isLidOpen() {
        return lidOpen;
    }

    public void setLidOpen(boolean lidOpen) {
        this.lidOpen = lidOpen;
    }

    public boolean isLensCasePresent() {
        return lensCasePresent;
    }

    public void setLensCasePresent(boolean lensCasePresent) {
        this.lensCasePresent = lensCasePresent;
    }

    public boolean isAlarmActive() {
        return alarmActive;
    }

    public void setAlarmActive(boolean alarmActive) {
        this.alarmActive = alarmActive;
    }

    public boolean isWifiConnected() {
        return wifiConnected;
    }

    public void setWifiConnected(boolean wifiConnected) {
        this.wifiConnected = wifiConnected;
    }

    public Integer getBatteryLevel() {
        return batteryLevel;
    }

    public void setBatteryLevel(Integer batteryLevel) {
        this.batteryLevel = batteryLevel;
    }

    public List<Event> getLastEvents() {
        return lastEvents;
    }

    public void setLastEvents(List<Event> lastEvents) {
        this.lastEvents = lastEvents;
    }
}
