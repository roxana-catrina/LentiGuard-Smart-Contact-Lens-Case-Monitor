package com.lentiguard.backend.repository;

import com.lentiguard.backend.entity.ScheduledAlarm;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import java.util.Optional;

public interface ScheduledAlarmRepository
        extends JpaRepository<ScheduledAlarm, Long> {

    List<ScheduledAlarm> findByDeviceId(Integer deviceId);
}