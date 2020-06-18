import sys
import re

with open(sys.argv[1], 'rb') as rom:
    for fname in sys.argv[2:]:
        with open(fname, 'r+') as fp:
            lines = []
            for line in fp:
                m = re.search(r'\.incbin "baserom.nds", (0x\w+), (0x\w+)', line)
                if m is not None:
                    addr = int(m[1], 16)
                    size = int(m[2], 16)
                    rom.seek(addr)
                    for i in range(0, size, 16):
                        data = rom.read(min(size - i, 16))
                        lines.append('\t.byte ' + ', '.join(f'0x{k:02X}' for k in data) + '\n')
                else:
                    lines.append(line)
            fp.seek(0)
            fp.truncate()
            fp.write(''.join(lines))
