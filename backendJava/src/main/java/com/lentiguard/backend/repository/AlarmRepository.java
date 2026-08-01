package com.lentiguard.backend.repository;

import com.lentiguard.backend.entity.Alarm;
import com.lentiguard.backend.entity.Event;
import org.springframework.data.jpa.repository.JpaRepository;

public interface AlarmRepository extends JpaRepository<Alarm, Long> {
}
