#ifndef NOTIFICATIONCONTROLLER_H
#define NOTIFICATIONCONTROLLER_H

#include "../models/Notification.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

class NotificationController {
private:
  std::vector<std::unique_ptr<Notification>> notifications;

public:
  NotificationController();
  ~NotificationController() = default;

  bool createNotification(const std::string &title, const std::string &text);
  bool markNotificationAsRead(int notificationIndex);

  const std::vector<std::unique_ptr<Notification>> &getAllNotifications() const;
  Notification *getNotification(int notificationIndex);

  bool isValidNotificationIndex(int notificationIndex) const;
  void loadNotifications();
};

#endif // NotificationController.h
