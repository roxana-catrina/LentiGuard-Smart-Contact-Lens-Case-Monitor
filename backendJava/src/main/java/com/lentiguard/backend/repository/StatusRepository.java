package com.lentiguard.backend.repository;

import com.lentiguard.backend.entity.Status;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface StatusRepository extends JpaRepository<Status, Long> {


    Optional<Status> findTopByOrderByCreatedAtDesc();
}