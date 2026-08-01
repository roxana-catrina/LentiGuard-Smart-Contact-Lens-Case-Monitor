package com.lentiguard.backend.service;

import com.lentiguard.backend.entity.Event;
import com.lentiguard.backend.repository.EventRepository;
import org.springframework.stereotype.Service;

@Service
public class EventService {

    private final EventRepository eventRepository;

    public EventService(EventRepository eventRepository) {
        this.eventRepository = eventRepository;

    }

    public void saveEvent(Event event) {
        eventRepository.save(event);
    }
}