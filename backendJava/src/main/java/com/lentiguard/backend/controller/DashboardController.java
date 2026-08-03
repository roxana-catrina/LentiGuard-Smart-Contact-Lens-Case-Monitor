package com.lentiguard.backend.controller;

import com.lentiguard.backend.dto.DashboardResponse;
import com.lentiguard.backend.service.DashboardService;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/dashboard")
public class DashboardController {

    private final DashboardService dashboardService;

    public DashboardController(DashboardService dashboardService) {
        this.dashboardService = dashboardService;
    }

    @GetMapping("/{deviceId}")
    public DashboardResponse getDashboard(@PathVariable Long deviceId) {

        return dashboardService.getDashboard(deviceId);

    }
}