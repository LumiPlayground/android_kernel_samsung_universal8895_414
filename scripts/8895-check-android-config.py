#!/usr/bin/env python3
"""Fail CI if Kconfig silently drops essential legacy Android bring-up features."""
import json
from pathlib import Path
import sys

required = {
    'CONFIG_ANDROID_BINDER_DEVICES': '"binder,hwbinder,vndbinder"',
}
for name in (
    'ANDROID_BINDER_IPC BPF_SYSCALL BPF_JIT BPF_JIT_ALWAYS_ON CGROUP_BPF '
    'NET_CLS_BPF NET_ACT_BPF CPUSETS MEMCG CGROUP_FREEZER CGROUP_PIDS '
    'CGROUP_DEVICE SECCOMP_FILTER BLK_DEV_INITRD RD_XZ EXT4_FS '
    'EXT4_ENCRYPTION F2FS_FS F2FS_FS_XATTR F2FS_FS_SECURITY '
    'F2FS_FS_ENCRYPTION FS_ENCRYPTION KEYS CRYPTO_XTS PSTORE_RAM'
).split():
    required['CONFIG_' + name] = 'y'
actual = {}
for line in Path(sys.argv[1]).read_text().splitlines():
    if line.startswith('CONFIG_') and '=' in line:
        key, value = line.split('=', 1)
        actual[key] = value
missing = {key: {'expected': value, 'actual': actual.get(key, 'disabled')}
           for key, value in required.items() if actual.get(key) != value}
print(json.dumps({'config_checks': len(required), 'mismatches': missing,
                  'hardware_boot_verified': False}, indent=2))
sys.exit(bool(missing))
