package com.lentiguard.backend.service;

import com.lentiguard.backend.entity.Status;
import com.lentiguard.backend.repository.StatusRepository;
import org.springframework.stereotype.Service;

@Service
public class StatusService {

    private final StatusRepository statusRepository;

    public StatusService(StatusRepository statusRepository) {
        this.statusRepository = statusRepository;
    }

    public void saveStatus(Status status) {
        statusRepository.save(status);
    }
}