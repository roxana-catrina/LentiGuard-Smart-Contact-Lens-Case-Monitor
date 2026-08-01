package com.lentiguard.backend.controller;


import com.lentiguard.backend.dto.EventRequest;
import com.lentiguard.backend.entity.Alarm;
import com.lentiguard.backend.service.AlarmService;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.time.LocalDateTime;

@RestController
@RequestMapping("/api/alarm")
public class AlarmController {
    private final AlarmService alarmService;

    public AlarmController(AlarmService alarmService) {
        this.alarmService = alarmService;
    }
    /*@PostMapping("/events")
    public void receiveAlarmEvent(@RequestBody EventRequest request)
    {
        System.out.println("Alarm Event");
        System.out.println("Device ID: " + request.getDeviceId());
        System.out.println("Event: " + request.getEvent());
    }*/


    @PostMapping("/events")
    public String receiveAlarmEvent(@RequestBody EventRequest request) {

        Alarm alarm = new Alarm();

        alarm.setDeviceId(request.getDeviceId());
        alarm.setEventType(request.getEvent());
        alarm.setCreatedAt(LocalDateTime.now());

        alarmService.saveAlarm(alarm);

        return "Alarm saved";
    }

}
