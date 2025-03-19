cmake_minimum_required(VERSION 3.5)

project(app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql LinguistTools)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql LinguistTools)

# Translation Files
set(TS_FILES
        translations/app_fr.ts
        translations/app_en.ts
)

# UI Files
set(UI_FILES
        ui/playerbox.ui
        ui/matchui.ui
        ui/playerprofileui.ui
        ui/scoreboardmatchdetailsui.ui
        ui/placesui.ui
        ui/reservationsui.ui
        ui/courtsui.ui
        ui/ticketsui.ui
        ui/scoreui.ui
        ui/clientsui.ui
        ui/seatsui.ui
        ui/settingsdialog.ui
)

# UI Header Files
set(UI_HEADERS
        ui/headers/playerbox.h
        ui/headers/matchui.h
        ui/headers/playerprofileui.h
        ui/headers/scoreboardmatchdetailsui.h
        ui/headers/placesui.h
        ui/headers/reservationsui.h
        ui/headers/courtsui.h
        ui/headers/ticketsui.h
        ui/headers/scoreui.h
        ui/headers/clientsui.h
        ui/headers/seatsui.h
        ui/headers/settingsdialog.h
)

# UI Source Files
set(UI_SOURCES
        ui/sources/playerbox.cpp
        ui/sources/matchui.cpp
        ui/sources/playerprofileui.cpp
        ui/sources/scoreboardmatchdetailsui.cpp
        ui/sources/placesui.cpp
        ui/sources/reservationsui.cpp
        ui/sources/courtsui.cpp
        ui/sources/ticketsui.cpp
        ui/sources/scoreui.cpp
        ui/sources/clientsui.cpp
        ui/sources/seatsui.cpp
        ui/sources/settingsdialog.cpp # Add the settings dialog source file
)

# Data Class Header Files (No .cpp files as constructors are inline)
set(DATA_HEADERS
        data/Player.h
        data/Match.h
        data/Client.h
        data/Seat.h
        data/Reservation.h
        data/Court.h
        data/Ticket.h
        data/Score.h
        data/Payment.h
)

# Gestion Class Header and Source Files
set(GESTION_HEADERS
        data/mgmt/PlayerManager.h
        data/mgmt/MatchManager.h
        data/mgmt/ClientManager.h
        data/mgmt/SeatManager.h
        data/mgmt/ReservationManager.h
        data/mgmt/CourtManager.h
        data/mgmt/TicketManager.h
        data/mgmt/PaymentManager.h
        data/mgmt/SeatManager.h
        data/mgmt/ScoreManager.h
)

set(GESTION_SOURCES
        data/mgmt/PlayerManager.cpp
        data/mgmt/MatchManager.cpp
        data/mgmt/ClientManager.cpp
        data/mgmt/SeatManager.cpp
        data/mgmt/ReservationManager.cpp
        data/mgmt/CourtManager.cpp
        data/mgmt/TicketManager.cpp
        data/mgmt/PaymentManager.cpp
        data/mgmt/ScoreManager.cpp
        data/mgmt/SeatManager.cpp
)

# All Source Files
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        ${UI_HEADERS}
        ${UI_SOURCES}
        ${UI_FILES}

        ${DATA_HEADERS}

        ${GESTION_HEADERS}
        ${GESTION_SOURCES}

        ${TS_FILES}
)

# Add the executable
# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#     qt_add_executable(app
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#     )
#     target_link_libraries(app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql) 

#     qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# else()
#     add_executable(app ${PROJECT_SOURCES})
#     target_link_libraries(app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql) 

#     qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# endif()

# Add Resources (Make sure to create the resources.qrc file)
#set(RESOURCES_FILES resources.qrc)
#target_sources(app PRIVATE ${RESOURCES_FILES})
#target_sources(app PRIVATE resources.qrc)

# Bundle Identifiers (Adjust based on your project)
# if(${QT_VERSION} VERSION_LESS 6.1.0)
#     set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.yourcompany.app)
# endif()
# set_target_properties(app PROPERTIES 
#     ${BUNDLE_ID_OPTION}
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# Installation (Adjust based on your preferences)
include(GNUInstallDirs)
# install(TARGETS app
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# Finalize Executable (Qt 6)
# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(app)
# endif()
