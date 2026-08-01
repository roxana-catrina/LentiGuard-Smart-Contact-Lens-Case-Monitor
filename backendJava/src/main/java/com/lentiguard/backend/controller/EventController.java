package com.lentiguard.backend.controller;

import com.lentiguard.backend.dto.EventRequest;

import com.lentiguard.backend.entity.Event;
import com.lentiguard.backend.service.EventService;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.time.LocalDateTime;

@RestController
@RequestMapping("/api")
public class EventController {
    private final EventService eventService;

    public EventController(EventService eventService) {
        this.eventService = eventService;
    }

   /* @PostMapping("/events")
    public void receiveEvent(@RequestBody EventRequest request) {

        System.out.println("Device ID: " + request.getDeviceId());
        System.out.println("Event: " + request.getEvent());

    }*/


    @PostMapping("/events")
    public String receiveEvent(@RequestBody EventRequest request) {
        Event event = new Event();

        event.setDeviceId(request.getDeviceId());
        event.setEventType(request.getEvent());
        event.setCreatedAt(LocalDateTime.now());

        eventService.saveEvent(event);
        return "Event saved";

    }

}