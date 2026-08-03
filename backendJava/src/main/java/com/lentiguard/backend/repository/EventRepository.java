package com.lentiguard.backend.repository;

import com.lentiguard.backend.entity.Device;
import com.lentiguard.backend.entity.Event;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface EventRepository extends JpaRepository<Event, Long> {
    List<Event> findTop10ByDeviceOrderByCreatedAtDesc(Device device);
}
