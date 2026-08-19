package com.lentiguard.backend.entity;


import jakarta.persistence.*;

import java.time.LocalTime;

@Entity
@Table(name = "scheduled_alarm")
public class ScheduledAlarm {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Integer deviceId;

    private LocalTime alarmTime;

    private boolean enabled;

    public ScheduledAlarm() {
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

    public LocalTime getAlarmTime() {
        return alarmTime;
    }

    public void setAlarmTime(LocalTime alarmTime) {
        this.alarmTime = alarmTime;
    }

    public boolean isEnabled() {
        return enabled;
    }

    public void setEnabled(boolean enabled) {
        this.enabled = enabled;
    }
}