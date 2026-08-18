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



    @PostMapping("/events")
    public String receiveEvent(@RequestBody EventRequest request) {

        eventService.processEvent(request);

        return "Event saved";
    }

    @GetMapping
    public List<Event> getAllEvents() {
        return eventService.getAllEvents();
    }
}