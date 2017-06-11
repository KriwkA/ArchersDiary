TEMPLATE = subdirs

SUBDIRS += \
    Core \
    Desktop

Core.subdir             = src/Core
Desktop.subdir          = src/Desktop

Desktop.depends         += Core
