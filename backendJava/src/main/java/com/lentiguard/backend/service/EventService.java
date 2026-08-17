package com.lentiguard.backend.service;

import com.lentiguard.backend.dto.EventRequest;
import com.lentiguard.backend.entity.Device;
import com.lentiguard.backend.entity.Event;
import com.lentiguard.backend.repository.DeviceRepository;
import com.lentiguard.backend.repository.EventRepository;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;

import com.lentiguard.backend.dto.DashboardUpdate;
import org.springframework.messaging.simp.SimpMessagingTemplate;

    @Service
    public class EventService {
        private final SimpMessagingTemplate messagingTemplate;
        private final EventRepository eventRepository;
        private final DeviceRepository deviceRepository;

        public EventService(
                EventRepository eventRepository,
                DeviceRepository deviceRepository,
                SimpMessagingTemplate messagingTemplate) {

            this.eventRepository = eventRepository;
            this.deviceRepository = deviceRepository;
            this.messagingTemplate = messagingTemplate;
        }

        public void saveEvent(Event event) {
            eventRepository.save(event);
        }

        public List<Event> getAllEvents() {
            return eventRepository.findAll();
        }

        public void processEvent(EventRequest request) {

            Device device = deviceRepository
                    .findById((long) request.getDeviceId())
                    .orElseThrow(() -> new RuntimeException("Device not found"));

            Event event = new Event();

            event.setDevice(device);
            event.setEventType(request.getEvent());
            event.setCreatedAt(LocalDateTime.now());

            eventRepository.save(event);
            messagingTemplate.convertAndSend(
                    "/topic/device/" + request.getDeviceId(),
                    "Event received: " + request.getEvent()
            );
        }
    }
