package com.lentiguard.backend.dto;

public class EventRequest {
    private int deviceId;
    private String event;

    public EventRequest(int deviceId, String event) {
        this.deviceId = deviceId;
        this.event = event;
    }

    public int getDeviceId() {
        return deviceId;
    }

    public String getEvent() {
        return event;
    }

    public void setDeviceId(int deviceId) {
        this.deviceId = deviceId;
    }

    public void setEvent(String event) {
        this.event = event;
    }
}
