package com.lentiguard.backend.service;
import com.lentiguard.backend.entity.ScheduledAlarm;
import com.lentiguard.backend.repository.ScheduledAlarmRepository;
import org.springframework.stereotype.Service;

import java.util.List;

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

    public List<ScheduledAlarm> getAlarms(Integer deviceId) {
        return scheduledAlarmRepository
                .findByDeviceId(deviceId);
    }

    public void deleteAlarm(Long alarmId) {
        scheduledAlarmRepository.deleteById(alarmId);
    }
}