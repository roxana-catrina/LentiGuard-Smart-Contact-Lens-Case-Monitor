package com.lentiguard.backend.service;

import com.lentiguard.backend.entity.Alarm;
import com.lentiguard.backend.repository.AlarmRepository;
import org.springframework.stereotype.Service;

@Service
public class AlarmService {

    private final AlarmRepository alarmRepository;

    public AlarmService(AlarmRepository alarmRepository) {
        this.alarmRepository = alarmRepository;
    }

    public void saveAlarm(Alarm alarm) {
        alarmRepository.save(alarm);
    }
}