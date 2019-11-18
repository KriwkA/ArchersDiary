TEMPLATE = subdirs

SUBDIRS += \
    BL \
    ArchersDiary

ArchersDiary.depends         += BL
