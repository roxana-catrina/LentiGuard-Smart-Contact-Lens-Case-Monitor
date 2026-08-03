package com.lentiguard.backend.service;

import com.lentiguard.backend.dto.DashboardResponse;
import com.lentiguard.backend.entity.Device;
import com.lentiguard.backend.entity.Event;
import com.lentiguard.backend.entity.Status;
import com.lentiguard.backend.repository.DeviceRepository;
import com.lentiguard.backend.repository.EventRepository;
import com.lentiguard.backend.repository.StatusRepository;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class DashboardService {

    private final DeviceRepository deviceRepository;
    private final StatusRepository statusRepository;
    private final EventRepository eventRepository;

    public DashboardService(DeviceRepository deviceRepository,
                            StatusRepository statusRepository,
                            EventRepository eventRepository) {

        this.deviceRepository = deviceRepository;
        this.statusRepository = statusRepository;
        this.eventRepository = eventRepository;
    }
    public DashboardResponse getDashboard(Long deviceId) {

        Device device = deviceRepository.findById(deviceId)
                .orElseThrow(() -> new RuntimeException("Device not found"));

        Status status = statusRepository
                .findTopByDeviceIdOrderByCreatedAtDesc(deviceId.intValue())
                .orElseThrow(() -> new RuntimeException("Status not found"));

        List<Event> events =
                eventRepository.findTop10ByDeviceOrderByCreatedAtDesc(device);

        DashboardResponse response = new DashboardResponse();

        response.setDeviceName(device.getName());
        response.setSerialNumber(device.getSerialNumber());

        response.setBatteryLevel(status.getBatteryLevel());
        response.setAlarmActive(status.isAlarmActive());
        response.setWifiConnected(status.isWifiConnected());
        response.setLidOpen(status.isLidOpen());
        response.setLensCasePresent(status.isLensCasePresent());

        response.setLastEvents(events);

        return response;
    }

}