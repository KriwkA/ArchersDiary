TEMPLATE = subdirs

SUBDIRS += \
    Core \
    ArchersDiary

Core.subdir             = src/Core
ArchersDiary.subdir          = src/ArchersDiary

ArchersDiary.depends         += Core
