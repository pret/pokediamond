import collections
import struct
import typing
import re

romfname = 'baserom.nds'
arm9offs = 0x00004000
arm9load = 0x02000000
mapheado = 0x020EEDBC
mapheads = 0x00003468


class MapHeader(typing.NamedTuple):
    area_data_bank: int
    move_model_bank: int
    matrix_id: int
    scripts_bank: int
    level_scripts_bank: int
    msg_bank: int
    day_music_id: int
    night_music_id: int
    wild_encounter_bank: int
    events_bank: int
    mapsec: int
    weather_type: int
    camera_type: int
    unk16: int
    battle_bg: int
    is_bike_allowed: bool
    is_running_allowed: bool
    is_escape_rope_allowed: bool
    is_fly_allowed: bool

    @classmethod
    def from_buffer(cls, buffer: bytes) -> typing.Generator['MapHeader', None, typing.Any]:
        for tup in struct.iter_unpack('<BBHHHHHHHHHBBBB', buffer):
            *tup, flags = tup
            tup += (flags & 15, flags & 16 != 0, flags & 32 != 0, flags & 64 != 0, flags & 128 != 0)
            yield cls._make(tup)


def read_sndseq_h():
    i = 0
    with open('include/constants/sndseq.h') as fp:
        for line in fp:
            if line.startswith('#define SEQ_'):
                name = line.split()[1]
                if name.startswith('SEQ_SE_'):
                    while i < 1500:
                        yield str(i)
                        i += 1
                elif not name.startswith('SEQ_PV'):
                    while i < 1000:
                        yield str(i)
                        i += 1
                yield name
                i += 1


def read_mapsec_h():
    with open('include/constants/map_sections.h') as fp:
        for line in fp:
            if line.startswith('#define MAPSEC_'):
                yield line.split()[1]


def read_naix(filename):
    with open(filename) as fp:
        for line in fp:
            if (m := re.match(r'\s*(NARC_\w+)\s+=\s+\d+,', line)) is not None:
                yield m[1]


class MyList(list):
    def __getitem__(self, item):
        try:
            return super().__getitem__(item)
        except IndexError:
            return str(item)


def main():
    sndseqs = MyList(read_sndseq_h())
    mapsecs = MyList(read_mapsec_h())
    msgnaix = MyList(read_naix('files/msgdata/msg.naix'))
    scrseqnaix = MyList(read_naix('files/fielddata/script/scr_seq_release.naix'))
    areanaix = MyList(read_naix('files/fielddata/areadata/area_data.naix'))
    mmlistnaix = MyList(read_naix('files/fielddata/mm_list/move_model_list.naix'))
    matlistnaix = MyList(read_naix('files/fielddata/mapmatrix/map_matrix.naix'))
    d_encdatanaix = MyList(read_naix('files/fielddata/encountdata/d_enc_data.naix'))
    p_encdatanaix = MyList(read_naix('files/fielddata/encountdata/p_enc_data.naix'))
    eventnaix = MyList(read_naix('files/fielddata/eventdata/zone_event_release.naix'))
    with open(romfname, 'rb') as rom:
        rom.seek(mapheado - arm9load + arm9offs)
        for header in MapHeader.from_buffer(rom.read(mapheads)):  # type: MapHeader
            print('{' + ', '.join((
                areanaix[header.area_data_bank],
                mmlistnaix[header.move_model_bank],
                matlistnaix[header.matrix_id],
                scrseqnaix[header.scripts_bank],
                scrseqnaix[header.level_scripts_bank],
                msgnaix[header.msg_bank],
                sndseqs[header.day_music_id],
                sndseqs[header.night_music_id],
                '0xFFFF' if header.wild_encounter_bank == 0xFFFF else 'ENCDATA({}, {})'.format(
                    d_encdatanaix[header.wild_encounter_bank],
                    p_encdatanaix[header.wild_encounter_bank],
                ),
                eventnaix[header.events_bank],
                mapsecs[header.mapsec],
                str(header.weather_type),
                str(header.camera_type),
                str(header.unk16),
                str(header.battle_bg),
                ['FALSE', 'TRUE'][header.is_bike_allowed],
                ['FALSE', 'TRUE'][header.is_running_allowed],
                ['FALSE', 'TRUE'][header.is_escape_rope_allowed],
                ['FALSE', 'TRUE'][header.is_fly_allowed],
            )) + '},')


if __name__ == '__main__':
    main()
