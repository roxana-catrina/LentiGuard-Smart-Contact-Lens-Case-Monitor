package com.lentiguard.backend.controller;

import com.lentiguard.backend.dto.EventRequest;

import com.lentiguard.backend.entity.Device;
import com.lentiguard.backend.entity.Event;
import com.lentiguard.backend.repository.DeviceRepository;
import com.lentiguard.backend.service.EventService;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.util.List;

@RestController
@RequestMapping("/api")
public class EventController {
    private final EventService eventService;
    private final DeviceRepository deviceRepository;

    public EventController(EventService eventService,
                           DeviceRepository deviceRepository) {

        this.eventService = eventService;
        this.deviceRepository = deviceRepository;
    }
   /* @PostMapping("/events")
    public void receiveEvent(@RequestBody EventRequest request) {

        System.out.println("Device ID: " + request.getDeviceId());
        System.out.println("Event: " + request.getEvent());

    }*/


    @PostMapping("/events")
    public String receiveEvent(@RequestBody EventRequest request) {

        Device device = deviceRepository
                .findById((long) request.getDeviceId())
                .orElseThrow(() -> new RuntimeException("Device not found"));

        Event event = new Event();

        event.setDevice(device);
        event.setEventType(request.getEvent());
        event.setCreatedAt(LocalDateTime.now());

        eventService.saveEvent(event);

        return "Event saved";
    }
}