package com.lentiguard.backend.entity;

import jakarta.persistence.*;

import java.time.LocalDateTime;

@Entity
@Table(name = "status")
public class Status {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Integer deviceId;

    private boolean lidOpen;

    private boolean lensCasePresent;

    private boolean alarmActive;

    private boolean wifiConnected;

    private Integer batteryLevel;

    private LocalDateTime createdAt;

    public Status() {
    }

    public Long getId() {
        return id;
    }

    public Integer getDeviceId() {
        return deviceId;
    }

    public void setDeviceId(Integer deviceId) {
        this.deviceId = deviceId;
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

    public LocalDateTime getCreatedAt() {
        return createdAt;
    }

    public void setCreatedAt(LocalDateTime createdAt) {
        this.createdAt = createdAt;
    }
}