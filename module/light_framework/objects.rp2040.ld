SECTIONS
{
    .light.modules :
    {
        . = ALIGN(4);
        __light_modules_start = .;
        KEEP(*(.light.modules))
        __light_modules_end = .;
        __light_modules_len = __light_modules_end - __light_modules_start;
    } > FLASH
}