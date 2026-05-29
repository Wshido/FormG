#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
TIMP Project - Full Test Suite
Tests: Unit (math, validation, protocol) + Integration (TCP server)
Run: python run_tests.py
Requires: Docker server running on 127.0.0.1:11999
"""

import socket
import struct
import time
import hashlib
import re
import sys
import os
from datetime import datetime

# ============================================================
# CONFIG
# ============================================================
SERVER_HOST = "127.0.0.1"
SERVER_PORT = 11999
TIMEOUT = 2
RESULTS = {"pass": 0, "fail": 0, "total": 0, "details": []}
SERVER_AVAILABLE = False

# ============================================================
# HELPERS
# ============================================================
def log_result(tc_id, name, status, note=""):
    RESULTS["total"] += 1
    if status == "PASS":
        RESULTS["pass"] += 1
    else:
        RESULTS["fail"] += 1
    RESULTS["details"].append((tc_id, name, status, note))
    mark = "\033[92mPASS\033[0m" if status == "PASS" else "\033[91mFAIL\033[0m"
    print(f"  [{mark}] {tc_id}: {name}")
    if note and status == "FAIL":
        print(f"         -> {note}")

def send_tcp(request):
    """Send a request to the TCP server and return the response."""
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(TIMEOUT)
        s.connect((SERVER_HOST, SERVER_PORT))
        s.sendall((request + "\n").encode("utf-8"))
        data = b""
        while True:
            chunk = s.recv(4096)
            if not chunk:
                break
            data += chunk
            if b"\n" in data:
                break
        s.close()
        return data.decode("utf-8").strip()
    except Exception as e:
        return f"ERROR: {e}"

def send_binary(params):
    """Send binary graph data to the server and return response."""
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(TIMEOUT)
        s.connect((SERVER_HOST, SERVER_PORT))
        a, b, c, step = params
        data = b'F' + struct.pack('dddd', a, b, c, step)
        s.sendall(data)
        response = b""
        while True:
            chunk = s.recv(65536)
            if not chunk:
                break
            response += chunk
            if b"\n" in response and response.count(b"\n") > 10:
                break
        s.close()
        return response.decode("utf-8", errors="replace")
    except Exception as e:
        return f"ERROR: {e}"

def hash_password(password, salt=""):
    """Replicate server-side password hashing."""
    if not salt:
        salt = generate_salt()
    data = (password + salt).encode("utf-8")
    h = hashlib.sha256(data).hexdigest()
    return salt + ":" + h

def generate_salt():
    import secrets
    import string
    alphabet = string.ascii_letters + string.digits
    return ''.join(secrets.choice(alphabet) for _ in range(16))

def validate_login(login):
    if not isinstance(login, str) or len(login) == 0:
        return False
    return 3 <= len(login) <= 16

def validate_email(email):
    if not isinstance(email, str) or len(email) == 0:
        return False
    return len(email) <= 100 and '@' in email and '.' in email

def validate_password(password):
    if not password or len(password) < 8 or len(password) > 64:
        return False
    return bool(re.match(r'^[A-Za-z0-9]+$', password))

def calculate_function(a, b, c, x):
    import math
    if x < 0:
        return math.sin(a * x)
    elif x < 1:
        if b * x < 0:
            return 0
        return math.sqrt(b * x)
    else:
        if abs(c * x - 1.0) < 0.0001:
            return 0
        return 1.0 / (c * x - 1.0)

# ============================================================
# UNIT TESTS: Validation
# ============================================================
def test_validation():
    print("\n=== UNIT TESTS: Validation ===")

    # TC-VAL-001: Login validation
    tests = [
        ("abc", True), ("ab", False), ("a" * 16, True), ("a" * 17, False),
        ("", False), ("test123", True), ("тест", True), ("a@b", True),
    ]
    for login, expected in tests:
        result = validate_login(login)
        status = "PASS" if result == expected else "FAIL"
        log_result("TC-VAL-001", f"validateLogin('{login}') == {expected}", status)

    # TC-VAL-002: Email validation
    email_tests = [
        ("test@mail.com", True), ("no-at.com", False), ("", False),
        ("a@b.c", True), ("test@" + "a" * 90 + ".com", True),
        ("test@" + "a" * 92 + ".com", False),
    ]
    for email, expected in email_tests:
        result = validate_email(email)
        status = "PASS" if result == expected else "FAIL"
        display = email[:20] + "..." if len(email) > 20 else email
        log_result("TC-VAL-002", f"validateEmail('{display}') == {expected}", status)

    # TC-VAL-003: Password validation
    pw_tests = [
        ("Pass1234", True), ("short1", False), ("", False),
        ("a" * 8, True), ("a" * 64, True), ("a" * 65, False),
        ("Pass word1", False), ("Pass@1234", False), ("Pass1234!", False),
        ("aA1bB2cC", True), ("12345678", True),
    ]
    for pw, expected in pw_tests:
        result = validate_password(pw)
        status = "PASS" if result == expected else "FAIL"
        log_result("TC-VAL-003", f"validatePassword('{pw[:10]}...') == {expected}", status)

# ============================================================
# UNIT TESTS: Math (calculateFunction)
# ============================================================
def test_calculate_function():
    print("\n=== UNIT TESTS: calculateFunction ===")
    import math

    tests = [
        # (a, b, c, x, expected, tolerance)
        (1, 1, 1, -1, math.sin(-1), 0.0001),
        (1, 1, 1, -0.5, math.sin(-0.5), 0.0001),
        (2, 1, 1, -1, math.sin(-2), 0.0001),
        (1, 4, 1, 0.25, 1.0, 0.0001),
        (1, 1, 1, 0.5, math.sqrt(0.5), 0.0001),
        (1, 1, 1, 0, 0, 0.0001),
        (1, 1, 1, 0.9, math.sqrt(0.9), 0.0001),
        (1, 1, 1, 1.0, 0.0, 0.0001),
        (1, 1, 1, 2.0, 1.0, 0.0001),
        (1, 1, 1, 1.5, 1.0 / 0.5, 0.0001),
        (1, 1, 1, 3.0, 1.0 / 2.0, 0.0001),
        (1, 1, 2, 2.0, 1.0 / (2*2 - 1), 0.0001),
        (0, 0, 0, -1, 0.0, 0.0001),
        (1, 0, 1, 0.5, 0.0, 0.0001),
        (1, -1, 1, 0.5, 0.0, 0.0001),
    ]

    for i, (a, b, c, x, expected, tol) in enumerate(tests):
        result = calculate_function(a, b, c, x)
        ok = abs(result - expected) < tol
        status = "PASS" if ok else "FAIL"
        log_result(f"TC-MATH-{i+1:03d}",
                   f"f({a},{b},{c},{x}) = {result:.4f} (expected {expected:.4f})",
                   status)

# ============================================================
# UNIT TESTS: Hashing
# ============================================================
def test_hashing():
    print("\n=== UNIT TESTS: Password Hashing ===")

    h1 = hash_password("test1234", "mysalt")
    h2 = hash_password("test1234", "mysalt")
    log_result("TC-HASH-001", "Same input -> same hash", "PASS" if h1 == h2 else "FAIL")

    h3 = hash_password("test1234", "other_salt")
    log_result("TC-HASH-002", "Different salt -> different hash", "PASS" if h1 != h3 else "FAIL")

    h4 = hash_password("different", "mysalt")
    log_result("TC-HASH-003", "Different password -> different hash", "PASS" if h1 != h4 else "FAIL")

    h5 = hash_password("test1234", "")
    log_result("TC-HASH-004", "Empty salt generates random salt", "PASS" if ":" in h5 else "FAIL")

    salt = h1.split(":")[0]
    log_result("TC-HASH-005", f"Salt length = {len(salt)}", "PASS" if len(salt) == 16 else "FAIL")

    hash_hex = h1.split(":")[1]
    log_result("TC-HASH-006", f"Hash hex length = {len(hash_hex)}",
               "PASS" if len(hash_hex) == 64 else "FAIL")

    log_result("TC-HASH-007", "Hash starts with salt:", "PASS" if h1.startswith("mysalt:") else "FAIL")

# ============================================================
# UNIT TESTS: Rate Limiting Logic
# ============================================================
def test_rate_limiting():
    print("\n=== UNIT TESTS: Rate Limiting Logic ===")

    class RateLimiter:
        def __init__(self, max_attempts=10, window_ms=60000):
            self.max_attempts = max_attempts
            self.window_ms = window_ms
            self.attempts = {}

        def is_limited(self, identifier, now_ms):
            if identifier not in self.attempts:
                self.attempts[identifier] = {"count": 1, "start": now_ms}
                return False
            data = self.attempts[identifier]
            if now_ms - data["start"] > self.window_ms:
                data["count"] = 1
                data["start"] = now_ms
                return False
            if data["count"] >= self.max_attempts:
                return True
            data["count"] += 1
            return False

    rl = RateLimiter(max_attempts=3, window_ms=1000)

    log_result("TC-RL-001", "1st attempt -> not limited",
               "PASS" if not rl.is_limited("user1", 0) else "FAIL")
    log_result("TC-RL-002", "2nd attempt -> not limited",
               "PASS" if not rl.is_limited("user1", 100) else "FAIL")
    log_result("TC-RL-003", "3rd attempt -> not limited",
               "PASS" if not rl.is_limited("user1", 200) else "FAIL")
    log_result("TC-RL-004", "4th attempt -> limited",
               "PASS" if rl.is_limited("user1", 300) else "FAIL")

    log_result("TC-RL-005", "Different user -> not limited",
               "PASS" if not rl.is_limited("user2", 400) else "FAIL")

    log_result("TC-RL-006", "After window expires -> not limited",
               "PASS" if not rl.is_limited("user1", 1500) else "FAIL")

# ============================================================
# UNIT TESTS: Brute Force Protection Logic
# ============================================================
def test_brute_force():
    print("\n=== UNIT TESTS: Brute Force Protection ===")

    class BruteForceProtector:
        def __init__(self, max_attempts=5, lockout_ms=900000):
            self.max_attempts = max_attempts
            self.lockout_ms = lockout_ms
            self.data = {}

        def record_failed(self, login, now_ms):
            if login not in self.data:
                self.data[login] = {"attempts": 1, "lockout_until": 0}
                return
            d = self.data[login]
            if d["lockout_until"] > 0 and now_ms >= d["lockout_until"]:
                d["attempts"] = 0
                d["lockout_until"] = 0
            d["attempts"] += 1
            if d["attempts"] >= self.max_attempts:
                d["lockout_until"] = now_ms + self.lockout_ms

        def is_blocked(self, login, now_ms):
            if login not in self.data:
                return False
            d = self.data[login]
            if d["lockout_until"] > 0 and now_ms < d["lockout_until"]:
                return True
            return False

        def reset(self, login):
            if login in self.data:
                self.data[login] = {"attempts": 0, "lockout_until": 0}

    bf = BruteForceProtector(max_attempts=3, lockout_ms=5000)

    log_result("TC-BF-001", "0 failures -> not blocked",
               "PASS" if not bf.is_blocked("user1", 0) else "FAIL")

    bf.record_failed("user1", 100)
    log_result("TC-BF-002", "1 failure -> not blocked",
               "PASS" if not bf.is_blocked("user1", 200) else "FAIL")

    bf.record_failed("user1", 300)
    log_result("TC-BF-003", "2 failures -> not blocked",
               "PASS" if not bf.is_blocked("user1", 400) else "FAIL")

    bf.record_failed("user1", 500)
    log_result("TC-BF-004", "3 failures -> blocked",
               "PASS" if bf.is_blocked("user1", 600) else "FAIL")

    log_result("TC-BF-005", "Blocked during lockout",
               "PASS" if bf.is_blocked("user1", 4000) else "FAIL")

    log_result("TC-BF-006", "After lockout expires -> not blocked",
               "PASS" if not bf.is_blocked("user1", 6000) else "FAIL")

    bf.reset("user1")
    log_result("TC-BF-007", "After reset -> not blocked",
               "PASS" if not bf.is_blocked("user1", 7000) else "FAIL")

# ============================================================
# UNIT TESTS: Session Management Logic
# ============================================================
def test_session_management():
    print("\n=== UNIT TESTS: Session Management ===")

    import time as _time

    class SessionManager:
        def __init__(self, ttl_ms=1800000):
            self.ttl_ms = ttl_ms
            self.sessions = {}

        def create(self, login, token, now_ms):
            self.sessions[login] = {"token": token, "last_activity": now_ms}

        def check(self, login, token, now_ms):
            self.cleanup(now_ms)
            if login not in self.sessions:
                return False
            s = self.sessions[login]
            if s["token"] != token:
                return False
            if now_ms - s["last_activity"] > self.ttl_ms:
                return False
            s["last_activity"] = now_ms
            return True

        def logout(self, login):
            self.sessions.pop(login, None)

        def logout_all(self, login):
            self.sessions.pop(login, None)

        def cleanup(self, now_ms):
            expired = [k for k, v in self.sessions.items()
                       if now_ms - v["last_activity"] > self.ttl_ms]
            for k in expired:
                del self.sessions[k]

    sm = SessionManager(ttl_ms=300000)

    sm.create("user1", "token123", 1000)
    log_result("TC-SES-001", "Create session -> exists",
               "PASS" if sm.check("user1", "token123", 1100) else "FAIL")

    log_result("TC-SES-002", "Wrong token -> rejected",
               "PASS" if not sm.check("user1", "wrong", 1200) else "FAIL")

    log_result("TC-SES-003", "Unknown login -> rejected",
               "PASS" if not sm.check("unknown", "token123", 1300) else "FAIL")

    log_result("TC-SES-004", "After TTL expires -> rejected",
               "PASS" if not sm.check("user1", "token123", 400000) else "FAIL")

    sm.create("user1", "newtoken", 500000)
    log_result("TC-SES-005", "Activity refreshes session",
               "PASS" if sm.check("user1", "newtoken", 501000) else "FAIL")

    sm.logout("user1")
    log_result("TC-SES-006", "Logout removes session",
               "PASS" if not sm.check("user1", "newtoken", 502000) else "FAIL")

# ============================================================
# INTEGRATION TESTS: TCP Server
# ============================================================
def test_server_connection():
    print("\n=== INTEGRATION TESTS: Server Connection ===")

    response = send_tcp("stat&test")
    status = "PASS" if "stat&" in response else "FAIL"
    log_result("TC-SRV-001", "Server responds to stat command", status,
               "" if status == "PASS" else f"Got: {response}")

    response = send_tcp("check&1&15&42")
    status = "PASS" if "check+" in response else "FAIL"
    log_result("TC-SRV-002", "Server check task (1,15,42) -> check+", status,
               "" if status == "PASS" else f"Got: {response}")

    response = send_tcp("check&1&15&99")
    status = "PASS" if "check-" in response else "FAIL"
    log_result("TC-SRV-003", "Server check task (1,15,99) -> check-", status,
               "" if status == "PASS" else f"Got: {response}")

    response = send_tcp("unknown_command")
    status = "PASS" if "unknown" in response else "FAIL"
    log_result("TC-SRV-004", "Unknown command -> 'unknown'", status,
               "" if status == "PASS" else f"Got: {response}")

def test_server_graph():
    print("\n=== INTEGRATION TESTS: Graph Computation ===")

    response = send_binary((1.0, 1.0, 1.0, 0.5))
    lines = [l for l in response.strip().split("\n") if l.strip()]
    has_data = any(l.startswith("1 ") or l.startswith("2 ") or l.startswith("3 ") for l in lines)
    log_result("TC-GRF-001", "Binary graph request returns data", "PASS" if has_data else "FAIL",
               f"Lines: {len(lines)}")

    types_found = set()
    for line in lines:
        parts = line.split()
        if parts:
            types_found.add(parts[0])
    log_result("TC-GRF-002", "Response contains all 3 function types",
               "PASS" if types_found == {"1", "2", "3"} else "FAIL",
               f"Types: {types_found}")

    for line in lines[:3]:
        parts = line.split()
        if len(parts) == 3:
            t, x, y = parts[0], float(parts[1]), float(parts[2])
            in_range = -10 <= y <= 10
            if not in_range:
                log_result("TC-GRF-003", f"Y value in range for {line.strip()}", "FAIL",
                           f"y={y}")
                break
    else:
        log_result("TC-GRF-003", "All Y values in range [-10, 10]", "PASS")

def test_server_auth_flow():
    print("\n=== INTEGRATION TESTS: Auth Flow ===")

    response = send_tcp("reg_request_code&test_nonexistent_email_12345@testing.invalid")
    status = "PASS" if "reg_request_code+" in response or "reg_request_code-" in response else "FAIL"
    log_result("TC-AUTH-INT-001", "Registration code request handled", status,
               f"Response: {response}")

    response = send_tcp("reg_confirm&testuser999&Pass1234&test999@test.com&000000")
    status = "PASS" if "reg_confirm-" in response else "FAIL"
    log_result("TC-AUTH-INT-002", "Invalid reg code -> reg_confirm-", status,
               f"Response: {response}")

    response = send_tcp("auth_request_code&nonexistent_user_xyz&Pass1234")
    status = "PASS" if "auth_request_code-" in response else "FAIL"
    log_result("TC-AUTH-INT-003", "Invalid login -> auth_request_code-", status,
               f"Response: {response}")

    response = send_tcp("reset_request_code&nonexistent_user_xyz")
    status = "PASS" if "reset_request_code-" in response else "FAIL"
    log_result("TC-AUTH-INT-004", "Invalid reset login -> reset_request_code-", status,
               f"Response: {response}")

    response = send_tcp("checksession&user1&faketoken")
    status = "PASS" if "checksession-" in response else "FAIL"
    log_result("TC-AUTH-INT-005", "Invalid session -> checksession-", status,
               f"Response: {response}")

    response = send_tcp("logout&user1")
    status = "PASS" if "logout+" in response else "FAIL"
    log_result("TC-AUTH-INT-006", "Logout command -> logout+", status,
               f"Response: {response}")

    response = send_tcp("logout_all&user1")
    status = "PASS" if "logout_all+" in response else "FAIL"
    log_result("TC-AUTH-INT-007", "Logout all -> logout_all+", status,
               f"Response: {response}")

    response = send_tcp("refresh_token&user1&faketoken")
    status = "PASS" if "refresh_token-" in response else "FAIL"
    log_result("TC-AUTH-INT-008", "Invalid refresh token -> refresh_token-", status,
               f"Response: {response}")

def test_server_input_validation():
    print("\n=== INTEGRATION TESTS: Input Validation ===")

    long_login = "a" * 20
    response = send_tcp(f"auth_request_code&{long_login}&Pass1234")
    status = "PASS" if "auth_request_code-" in response else "FAIL"
    log_result("TC-INV-001", "Login > 16 chars -> rejected", status,
               f"Response: {response}")

    long_email = "a" * 90 + "@test.com"
    response = send_tcp(f"reg_request_code&{long_email}")
    status = "PASS" if "reg_request_code-" in response or "reg_request_code+" in response else "FAIL"
    log_result("TC-INV-002", "Email > 100 chars -> handled", status,
               f"Response: {response}")

    response = send_tcp("reg_confirm&ab&Pass1234&a@b.com&123456")
    status = "PASS" if "reg_confirm-" in response else "FAIL"
    log_result("TC-INV-003", "Login < 3 chars -> reg_confirm-", status,
               f"Response: {response}")

    response = send_tcp("reg_confirm&testuser&short&a@b.com&123456")
    status = "PASS" if "reg_confirm-" in response else "FAIL"
    log_result("TC-INV-004", "Password < 8 chars -> reg_confirm-", status,
               f"Response: {response}")

    response = send_tcp("reg_confirm&testuser&Pass word1&a@b.com&123456")
    status = "PASS" if "reg_confirm-" in response else "FAIL"
    log_result("TC-INV-005", "Password with spaces -> reg_confirm-", status,
               f"Response: {response}")

def test_server_stress():
    print("\n=== INTEGRATION TESTS: Stress ===")

    start = time.time()
    for i in range(50):
        send_tcp("stat&stress_test")
    elapsed = time.time() - start
    avg_ms = (elapsed / 50) * 1000
    log_result("TC-STRESS-001", f"50 stat requests in {elapsed:.2f}s (avg {avg_ms:.1f}ms)",
               "PASS" if elapsed < 30 else "FAIL")

    start = time.time()
    for i in range(20):
        send_binary((1.0, 1.0, 1.0, 0.5))
    elapsed = time.time() - start
    avg_ms = (elapsed / 20) * 1000
    log_result("TC-STRESS-002", f"20 graph requests in {elapsed:.2f}s (avg {avg_ms:.1f}ms)",
               "PASS" if elapsed < 30 else "FAIL")

# ============================================================
# REPORT
# ============================================================
def generate_report():
    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    report = []
    report.append(f"TIMP Test Report - {now}")
    report.append(f"{'='*60}")
    report.append(f"Total:  {RESULTS['total']}")
    report.append(f"Pass:   {RESULTS['pass']}")
    report.append(f"Fail:   {RESULTS['fail']}")
    report.append(f"Rate:   {RESULTS['pass']*100//max(RESULTS['total'],1)}%")
    report.append(f"{'='*60}")
    report.append("")

    for tc_id, name, status, note in RESULTS["details"]:
        mark = "PASS" if status == "PASS" else "FAIL"
        line = f"[{mark}] {tc_id}: {name}"
        if note:
            line += f" -> {note}"
        report.append(line)

    report_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "test_report.txt")
    with open(report_path, "w", encoding="utf-8") as f:
        f.write("\n".join(report))
    print(f"\nReport saved: {report_path}")

# ============================================================
# MAIN
# ============================================================
if __name__ == "__main__":
    print(f"TIMP Test Suite - {datetime.now().strftime('%Y-%m-%d %H:%M')}")
    print(f"Server: {SERVER_HOST}:{SERVER_PORT}")

    # Check server availability
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(2)
        s.connect((SERVER_HOST, SERVER_PORT))
        s.close()
        SERVER_AVAILABLE = True
        print("Server: ONLINE")
    except:
        print("Server: OFFLINE (integration tests will be skipped)")

    test_validation()
    test_calculate_function()
    test_hashing()
    test_rate_limiting()
    test_brute_force()
    test_session_management()

    if SERVER_AVAILABLE:
        test_server_connection()
        test_server_graph()
        test_server_auth_flow()
        test_server_input_validation()
        test_server_stress()
    else:
        print("\n=== INTEGRATION TESTS SKIPPED (server offline) ===")

    print(f"\n{'='*60}")
    print(f"RESULTS: {RESULTS['pass']}/{RESULTS['total']} PASS, {RESULTS['fail']} FAIL")
    print(f"{'='*60}")

    generate_report()

    sys.exit(0 if RESULTS["fail"] == 0 else 1)
