package com.lentiguard.backend.controller;

import com.lentiguard.backend.dto.EventRequest;
import com.lentiguard.backend.dto.StatusRequest;
import com.lentiguard.backend.entity.Status;
import com.lentiguard.backend.service.StatusService;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.time.LocalDateTime;

@RestController
@RequestMapping("/api")
public class StatusController {
    private final StatusService statusService;

    public StatusController(StatusService statusService) {
        this.statusService = statusService;
    }

    /* @PostMapping("/status")
     public String getStatus(@RequestBody StatusRequest request) {
         System.out.println("Device ID: " + request.getDeviceId());
         System.out.println("Lid Open: " + request.isLidOpen());
         System.out.println("Battery Level: " + request.getBatteryLevel());
         System.out.println("Lens Case Present: " + request.isLensCasePresent());
         System.out.println("Alarm Active: " + request.isAlarmActive());
         System.out.println("WiFi Connected: " + request.isWifiConnected());
         return "Status received";
     }
     */
    @PostMapping("/status")
    public String receiveStatus(@RequestBody StatusRequest request) {

        Status status = new Status();

        status.setDeviceId(request.getDeviceId());
        status.setLidOpen(request.isLidOpen());
        status.setLensCasePresent(request.isLensCasePresent());
        status.setAlarmActive(request.isAlarmActive());
        status.setWifiConnected(request.isWifiConnected());
        status.setBatteryLevel(request.getBatteryLevel());
        status.setCreatedAt(LocalDateTime.now());

        statusService.saveStatus(status);

        return "Status saved";
    }
}
