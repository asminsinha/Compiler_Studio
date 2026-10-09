import React, { useState } from 'react';
import { VMState, Quad } from '../types';
import { Play, Pause, StepForward, StepBack, RotateCcw, AlertTriangle, Terminal, Cpu } from 'lucide-react';

interface Props {
  vmState: VMState | null;
  quads: Quad[];
  onStepForward: () => void;
  onStepBackward: () => void;
  onRunAll: () => void;
  onReset: () => void;
  isLoading: boolean;
}

export const VirtualExecution: React.FC<Props> = ({
  vmState,
  quads,
  onStepForward,
  onStepBackward,
  onRunAll,
  onReset,
  isLoading,
}) => {
  return (
    <div style={{ display: 'flex', flexDirection: 'column', height: '100%', background: 'var(--bg-primary)' }}>
      {/* Control Toolbar */}
      <div
        style={{
          padding: '10px 16px',
          borderBottom: '1px solid var(--border-color)',
          background: 'var(--bg-secondary)',
          display: 'flex',
          gap: 10,
          alignItems: 'center',
        }}
      >
        <button className="btn btn-primary" onClick={onRunAll} disabled={isLoading || vmState?.is_halted}>
          <Play size={14} /> Run to Completion
        </button>
        <button className="btn btn-secondary" onClick={onStepForward} disabled={isLoading || vmState?.is_halted}>
          <StepForward size={14} /> Step Forward
        </button>
        <button className="btn btn-secondary" onClick={onStepBackward} disabled={isLoading || !vmState?.can_step_back}>
          <StepBack size={14} /> Step Backward (Reversible)
        </button>
        <button className="btn btn-secondary" onClick={onReset} disabled={isLoading}>
          <RotateCcw size={14} /> Reset
        </button>

        <div style={{ marginLeft: 'auto', display: 'flex', gap: 12, alignItems: 'center', fontSize: '12px' }}>
          <span style={{ color: 'var(--text-muted)' }}>Status:</span>
          <span
            className={`badge ${
              vmState?.status === 'COMPLETED'
                ? 'badge-green'
                : vmState?.status === 'LIMIT_EXCEEDED'
                ? 'badge-red'
                : 'badge-blue'
            }`}
          >
            {vmState?.status || 'READY'}
          </span>
          <span style={{ color: 'var(--text-muted)' }}>Steps:</span>
          <span style={{ fontWeight: 600 }}>{vmState?.steps || 0}</span>
          <span style={{ color: 'var(--text-muted)' }}>PC:</span>
          <span className="mono" style={{ color: 'var(--accent-cyan)' }}>L{vmState?.pc ?? 0}</span>
        </div>
      </div>

      {/* Main Execution View */}
      <div style={{ display: 'grid', gridTemplateColumns: '1.2fr 1fr', flex: 1, overflow: 'hidden' }}>
        {/* Left: TAC with Program Counter indicator */}
        <div style={{ borderRight: '1px solid var(--border-color)', display: 'flex', flexDirection: 'column' }}>
          <div style={{ padding: '8px 12px', background: 'var(--bg-tertiary)', borderBottom: '1px solid var(--border-color)', fontSize: '12px', fontWeight: 600, color: 'var(--text-secondary)' }}>
            INTERMEDIATE CODE & EXECUTION TRACE
          </div>
          <div style={{ flex: 1, overflowY: 'auto', padding: '12px', background: 'var(--bg-secondary)' }} className="mono">
            {quads.map((q) => {
              const isCurrent = vmState?.pc === q.id;
              let text = '';
              if (q.op === '=') text = `${q.result} = ${q.arg1}`;
              else if (q.op === 'print') text = `print ${q.arg1}`;
              else if (q.op === 'print_str') text = `print ${q.arg1}`;
              else if (q.op === 'goto') text = `goto L${q.result}`;
              else if (['<', '>', '<=', '>=', '==', '!='].includes(q.op))
                text = `if ${q.arg1} ${q.op} ${q.arg2} goto L${q.result}`;
              else text = `${q.result} = ${q.arg1} ${q.op} ${q.arg2}`;

              return (
                <div
                  key={q.id}
                  style={{
                    padding: '4px 8px',
                    borderRadius: 'var(--radius-sm)',
                    background: isCurrent ? 'rgba(59, 130, 246, 0.2)' : 'transparent',
                    borderLeft: isCurrent ? '3px solid var(--accent-blue)' : '3px solid transparent',
                    display: 'flex',
                    alignItems: 'center',
                    gap: 12,
                    fontSize: '13px',
                  }}
                >
                  <span style={{ color: isCurrent ? 'var(--accent-blue)' : 'var(--text-muted)', width: 28 }}>
                    {isCurrent ? '▶' : ''}
                  </span>
                  <span style={{ color: 'var(--accent-cyan)', width: 36 }}>L{q.id}:</span>
                  <span style={{ color: isCurrent ? '#ffffff' : 'var(--text-primary)', fontWeight: isCurrent ? 600 : 400 }}>
                    {text}
                  </span>
                </div>
              );
            })}
          </div>
        </div>

        {/* Right: Runtime Memory & Console Output */}
        <div style={{ display: 'grid', gridTemplateRows: '1fr 1fr', overflow: 'hidden' }}>
          {/* Virtual Variable Store */}
          <div style={{ borderBottom: '1px solid var(--border-color)', padding: '12px', overflowY: 'auto' }}>
            <div style={{ fontSize: '12px', fontWeight: 600, color: 'var(--text-secondary)', marginBottom: 8, display: 'flex', alignItems: 'center', gap: 6 }}>
              <Cpu size={14} /> VIRTUAL VARIABLE STORE (MEMORY MAP)
            </div>
            {Object.keys(vmState?.user_variables || {}).length === 0 ? (
              <div style={{ fontSize: '12px', color: 'var(--text-muted)' }}>No variables instantiated.</div>
            ) : (
              <table style={{ width: '100%', borderCollapse: 'collapse', fontSize: '12px' }} className="mono">
                <thead>
                  <tr style={{ borderBottom: '1px solid var(--border-color)', color: 'var(--text-muted)' }}>
                    <th style={{ padding: '4px 8px', textAlign: 'left' }}>Variable</th>
                    <th style={{ padding: '4px 8px', textAlign: 'left' }}>Current Value</th>
                    <th style={{ padding: '4px 8px', textAlign: 'left' }}>Type</th>
                  </tr>
                </thead>
                <tbody>
                  {Object.entries(vmState?.user_variables || {}).map(([name, val]) => (
                    <tr key={name} style={{ borderBottom: '1px solid var(--border-color)' }}>
                      <td style={{ padding: '6px 8px', color: 'var(--accent-cyan)', fontWeight: 600 }}>{name}</td>
                      <td style={{ padding: '6px 8px', color: 'var(--accent-green)', fontWeight: 700 }}>{val}</td>
                      <td style={{ padding: '6px 8px', color: 'var(--text-muted)' }}>int (32-bit)</td>
                    </tr>
                  ))}
                </tbody>
              </table>
            )}
          </div>

          {/* Console Output */}
          <div style={{ padding: '12px', display: 'flex', flexDirection: 'column', background: '#0a0c10' }}>
            <div style={{ fontSize: '12px', fontWeight: 600, color: 'var(--text-secondary)', marginBottom: 8, display: 'flex', alignItems: 'center', gap: 6 }}>
              <Terminal size={14} /> RUNTIME CONSOLE OUTPUT
            </div>
            <div
              style={{
                flex: 1,
                overflowY: 'auto',
                fontSize: '12px',
                lineHeight: 1.6,
                color: 'var(--accent-green)',
                fontFamily: 'var(--font-mono)',
              }}
            >
              {vmState?.console_output && vmState.console_output.length > 0 ? (
                vmState.console_output.map((out, idx) => (
                  <div key={idx} style={{ display: 'flex', gap: 8 }}>
                    <span style={{ color: 'var(--text-muted)' }}>&gt;</span>
                    <span>{out}</span>
                  </div>
                ))
              ) : (
                <span style={{ color: 'var(--text-muted)' }}>No console output produced yet.</span>
              )}
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};
