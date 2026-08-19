package com.lentiguard.backend.service;

import com.lentiguard.backend.entity.ScheduledAlarm;
import com.lentiguard.backend.repository.ScheduledAlarmRepository;
import org.springframework.stereotype.Service;

@Service
public class ScheduledAlarmService {

    private final ScheduledAlarmRepository scheduledAlarmRepository;

    public ScheduledAlarmService(
            ScheduledAlarmRepository scheduledAlarmRepository) {

        this.scheduledAlarmRepository = scheduledAlarmRepository;
    }

    public ScheduledAlarm saveAlarm(ScheduledAlarm alarm) {
        return scheduledAlarmRepository.save(alarm);
    }

    public ScheduledAlarm getAlarm(Integer deviceId) {
        return scheduledAlarmRepository
                .findByDeviceId(deviceId)
                .orElse(null);
    }
}