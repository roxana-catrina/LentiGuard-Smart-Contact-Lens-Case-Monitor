package com.lentiguard.backend.service;

import com.lentiguard.backend.entity.Device;
import com.lentiguard.backend.repository.DeviceRepository;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class DeviceService {

    private final DeviceRepository deviceRepository;

    public DeviceService(DeviceRepository deviceRepository) {
        this.deviceRepository = deviceRepository;
    }

    public void saveDevice(Device device) {
        deviceRepository.save(device);
    }
    public List<Device> getAllDevices() {
        return deviceRepository.findAll();
    }
    public Device getDevice(Long id) {
        return deviceRepository.findById(id)
                .orElseThrow(() -> new RuntimeException("Device not found"));
    }
}