package com.lentiguard.backend.controller;

import com.lentiguard.backend.dto.DeviceRequest;
import com.lentiguard.backend.entity.Device;
import com.lentiguard.backend.service.DeviceService;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.util.List;

@RestController
@RequestMapping("/api/devices")
public class DeviceController {

    private final DeviceService deviceService;

    public DeviceController(DeviceService deviceService) {
        this.deviceService = deviceService;
    }

    @PostMapping
    public String createDevice(@RequestBody DeviceRequest request) {

        Device device = new Device();

        device.setName(request.getName());
        device.setSerialNumber(request.getSerialNumber());
        device.setFirmwareVersion(request.getFirmwareVersion());
        device.setRegisteredAt(LocalDateTime.now());

        deviceService.saveDevice(device);

        return "Device saved";
    }

    @GetMapping
    public List<Device> getAllDevices() {
        return deviceService.getAllDevices();
    }
    @GetMapping("/{id}")
    public Device getDevice(@PathVariable Long id) {
        return deviceService.getDevice(id);
    }
}