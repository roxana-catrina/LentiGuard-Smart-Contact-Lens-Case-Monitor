package com.lentiguard.backend.controller;
import com.lentiguard.backend.entity.ScheduledAlarm;
import com.lentiguard.backend.service.ScheduledAlarmService;
import org.springframework.web.bind.annotation.*;

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
    public ScheduledAlarm getAlarm(
            @PathVariable Integer deviceId) {

        return scheduledAlarmService.getAlarm(deviceId);
    }
}