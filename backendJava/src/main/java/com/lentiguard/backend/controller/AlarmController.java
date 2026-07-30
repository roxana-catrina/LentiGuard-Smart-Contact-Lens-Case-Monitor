package com.lentiguard.backend.controller;


import com.lentiguard.backend.dto.EventRequest;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api/alarm")
public class AlarmController {

    @PostMapping("/events")
    public void receiveAlarmEvent(@RequestBody EventRequest request)
    {
        System.out.println("Alarm Event");
        System.out.println("Device ID: " + request.getDeviceId());
        System.out.println("Event: " + request.getEvent());
    }

}
