package com.lentiguard.backend.dto;


public class DashboardUpdate {

    private Long deviceId;
    private Integer batteryLevel;
    private Boolean lidOpen;
    private Boolean lensCasePresent;
    private Boolean alarmActive;
    private Boolean wifiConnected;

    public DashboardUpdate() {
    }

    public Long getDeviceId() {
        return deviceId;
    }

    public void setDeviceId(Long deviceId) {
        this.deviceId = deviceId;
    }

    public Integer getBatteryLevel() {
        return batteryLevel;
    }

    public void setBatteryLevel(Integer batteryLevel) {
        this.batteryLevel = batteryLevel;
    }

    public Boolean getLidOpen() {
        return lidOpen;
    }

    public void setLidOpen(Boolean lidOpen) {
        this.lidOpen = lidOpen;
    }

    public Boolean getLensCasePresent() {
        return lensCasePresent;
    }

    public void setLensCasePresent(Boolean lensCasePresent) {
        this.lensCasePresent = lensCasePresent;
    }

    public Boolean getAlarmActive() {
        return alarmActive;
    }

    public void setAlarmActive(Boolean alarmActive) {
        this.alarmActive = alarmActive;
    }

    public Boolean getWifiConnected() {
        return wifiConnected;
    }

    public void setWifiConnected(Boolean wifiConnected) {
        this.wifiConnected = wifiConnected;
    }
}