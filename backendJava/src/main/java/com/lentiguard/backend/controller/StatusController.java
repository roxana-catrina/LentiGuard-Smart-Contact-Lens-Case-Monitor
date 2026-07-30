package com.lentiguard.backend.controller;

import com.lentiguard.backend.dto.EventRequest;
import com.lentiguard.backend.dto.StatusRequest;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api")
public class StatusController {

    @PostMapping("/status")
    public String getStatus(@RequestBody StatusRequest request) {
        System.out.println("Device ID: " + request.getDeviceId());
        System.out.println("Lid Open: " + request.isLidOpen());
        System.out.println("Battery Level: " + request.getBatteryLevel());
        System.out.println("Lens Case Present: " + request.isLensCasePresent());
        System.out.println("Alarm Active: " + request.isAlarmActive());
        System.out.println("WiFi Connected: " + request.isWifiConnected());
        return "Status received";
    }
}
