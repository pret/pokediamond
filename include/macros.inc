.macro glabel label
    .global \label
    .thumb
    \label:
.endm
