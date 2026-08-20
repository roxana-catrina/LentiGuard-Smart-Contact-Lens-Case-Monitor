package com.lentiguard.backend.controller;

import com.lentiguard.backend.entity.ScheduledAlarm;
import com.lentiguard.backend.service.ScheduledAlarmService;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/alarm")
public class ScheduledAlarmController {

    private final ScheduledAlarmService scheduledAlarmService;

    public ScheduledAlarmController(
            ScheduledAlarmService scheduledAlarmService) {

        this.scheduledAlarmService = scheduledAlarmService;
    }

    @PostMapping("/schedule")
    public ScheduledAlarm setAlarm(
            @RequestBody ScheduledAlarm alarm) {

        return scheduledAlarmService.saveAlarm(alarm);
    }

    @GetMapping("/{deviceId}")
    public List<ScheduledAlarm> getAlarms(
            @PathVariable Integer deviceId) {

        return scheduledAlarmService.getAlarms(deviceId);
    }

    @DeleteMapping("/{alarmId}")
    public void deleteAlarm(
            @PathVariable Long alarmId) {

        scheduledAlarmService.deleteAlarm(alarmId);
    }
}