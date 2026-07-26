package com.lentiguard.backend.controller;

import com.lentiguard.backend.dto.EventRequest;

import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api")
public class EventController {

    @PostMapping("/events")
    public void receiveEvent(@RequestBody EventRequest request) {

        System.out.println("Device ID: " + request.getDeviceId());
        System.out.println("Event: " + request.getEvent());

    }
}