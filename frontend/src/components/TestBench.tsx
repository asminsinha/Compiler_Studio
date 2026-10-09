import React, { useState } from 'react';
import { Play, CheckCircle2, XCircle, RotateCcw } from 'lucide-react';

interface TestCase {
  id: string;
  name: string;
  status: 'PASS' | 'FAIL';
  duration_ms: number;
  message: string;
}

interface TestReport {
  total: number;
  passed: number;
  failed: number;
  results: TestCase[];
}

export const TestBench: React.FC = () => {
  const [isRunning, setIsRunning] = useState(false);
  const [report, setReport] = useState<TestReport | null>(null);

  const runAllTests = async () => {
    setIsRunning(true);
    try {
      const res = await fetch('/api/tests/run', { method: 'POST' });
      const data = await res.json();
      setReport(data);
    } catch (e) {
      console.error(e);
    } finally {
      setIsRunning(false);
    }
  };

  return (
    <div style={{ display: 'flex', flexDirection: 'column', height: '100%', background: 'var(--bg-primary)', padding: '16px', overflowY: 'auto' }}>
      {/* Test Controls */}
      <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: 16 }}>
        <div>
          <h2 style={{ fontSize: '16px', fontWeight: 700, color: 'var(--text-primary)' }}>
            Compiler Test Bench & Automated Verification Suite
          </h2>
          <div style={{ fontSize: '12px', color: 'var(--text-muted)' }}>
            Regression tests, loop control-flow verifications, backpatching correctness, and diagnostics
          </div>
        </div>
        <button className="btn btn-primary" onClick={runAllTests} disabled={isRunning}>
          <Play size={14} /> {isRunning ? 'Running Suite...' : 'Execute All Tests'}
        </button>
      </div>

      {report && (
        <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 12, marginBottom: 16 }}>
          <div style={{ background: 'var(--bg-secondary)', padding: '12px', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)' }}>
            <div style={{ fontSize: '11px', color: 'var(--text-muted)' }}>TOTAL TESTS</div>
            <div style={{ fontSize: '20px', fontWeight: 700 }}>{report.total}</div>
          </div>
          <div style={{ background: 'var(--bg-secondary)', padding: '12px', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)' }}>
            <div style={{ fontSize: '11px', color: 'var(--text-muted)' }}>PASSED</div>
            <div style={{ fontSize: '20px', fontWeight: 700, color: 'var(--accent-green)' }}>{report.passed}</div>
          </div>
          <div style={{ background: 'var(--bg-secondary)', padding: '12px', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)' }}>
            <div style={{ fontSize: '11px', color: 'var(--text-muted)' }}>FAILED</div>
            <div style={{ fontSize: '20px', fontWeight: 700, color: report.failed > 0 ? 'var(--accent-red)' : 'var(--accent-green)' }}>
              {report.failed}
            </div>
          </div>
        </div>
      )}

      {/* Test Results Table */}
      <div style={{ background: 'var(--bg-secondary)', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)', overflow: 'hidden' }}>
        <table style={{ width: '100%', borderCollapse: 'collapse', fontSize: '12px' }}>
          <thead>
            <tr style={{ borderBottom: '1px solid var(--border-color)', background: 'var(--bg-tertiary)', color: 'var(--text-muted)', textAlign: 'left' }}>
              <th style={{ padding: '8px 12px' }}>Test ID</th>
              <th style={{ padding: '8px 12px' }}>Suite & Description</th>
              <th style={{ padding: '8px 12px' }}>Result</th>
              <th style={{ padding: '8px 12px' }}>Duration</th>
              <th style={{ padding: '8px 12px' }}>Verification Notes</th>
            </tr>
          </thead>
          <tbody>
            {report ? (
              report.results.map((t) => (
                <tr key={t.id} style={{ borderBottom: '1px solid var(--border-color)' }}>
                  <td style={{ padding: '8px 12px', fontWeight: 600, color: 'var(--accent-cyan)' }} className="mono">
                    {t.id}
                  </td>
                  <td style={{ padding: '8px 12px', color: 'var(--text-primary)', fontWeight: 500 }}>{t.name}</td>
                  <td style={{ padding: '8px 12px' }}>
                    {t.status === 'PASS' ? (
                      <span className="badge badge-green" style={{ display: 'inline-flex', gap: 4, alignItems: 'center' }}>
                        <CheckCircle2 size={12} /> PASS
                      </span>
                    ) : (
                      <span className="badge badge-red" style={{ display: 'inline-flex', gap: 4, alignItems: 'center' }}>
                        <XCircle size={12} /> FAIL
                      </span>
                    )}
                  </td>
                  <td style={{ padding: '8px 12px', color: 'var(--text-muted)' }} className="mono">
                    {t.duration_ms}ms
                  </td>
                  <td style={{ padding: '8px 12px', color: 'var(--text-secondary)' }}>{t.message}</td>
                </tr>
              ))
            ) : (
              <tr>
                <td colSpan={5} style={{ padding: '32px', textAlign: 'center', color: 'var(--text-muted)' }}>
                  Click "Execute All Tests" to run regression checks against the native Flex/Bison compiler.
                </td>
              </tr>
            )}
          </tbody>
        </table>
      </div>
    </div>
  );
};
