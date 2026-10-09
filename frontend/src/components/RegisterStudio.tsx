import React from 'react';
import { RegisterAnalysis } from '../types';
import { Layers, Activity, Server, AlertCircle } from 'lucide-react';

interface Props {
  analysis: RegisterAnalysis;
  quadCount: number;
}

export const RegisterStudio: React.FC<Props> = ({ analysis, quadCount }) => {
  return (
    <div style={{ display: 'flex', flexDirection: 'column', height: '100%', background: 'var(--bg-primary)', overflowY: 'auto', padding: '16px' }}>
      {/* Header Metric Cards */}
      <div style={{ display: 'grid', gridTemplateColumns: 'repeat(4, 1fr)', gap: 12, marginBottom: 16 }}>
        <div style={{ background: 'var(--bg-secondary)', padding: '12px', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)' }}>
          <div style={{ fontSize: '11px', color: 'var(--text-muted)', marginBottom: 4 }}>AVAILABLE REGISTERS</div>
          <div style={{ fontSize: '20px', fontWeight: 700, color: 'var(--accent-blue)' }}>K = {analysis.k_registers}</div>
          <div style={{ fontSize: '11px', color: 'var(--text-secondary)' }}>{analysis.available_registers.join(', ')}</div>
        </div>

        <div style={{ background: 'var(--bg-secondary)', padding: '12px', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)' }}>
          <div style={{ fontSize: '11px', color: 'var(--text-muted)', marginBottom: 4 }}>PEAK LIVE VARIABLES</div>
          <div style={{ fontSize: '20px', fontWeight: 700, color: 'var(--accent-cyan)' }}>{analysis.peak_live}</div>
          <div style={{ fontSize: '11px', color: 'var(--text-secondary)' }}>Simultaneous live ranges</div>
        </div>

        <div style={{ background: 'var(--bg-secondary)', padding: '12px', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)' }}>
          <div style={{ fontSize: '11px', color: 'var(--text-muted)', marginBottom: 4 }}>REGISTER ALLOCATIONS</div>
          <div style={{ fontSize: '20px', fontWeight: 700, color: 'var(--accent-green)' }}>
            {Object.keys(analysis.allocations).length}
          </div>
          <div style={{ fontSize: '11px', color: 'var(--text-secondary)' }}>Successfully colored</div>
        </div>

        <div style={{ background: 'var(--bg-secondary)', padding: '12px', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)' }}>
          <div style={{ fontSize: '11px', color: 'var(--text-muted)', marginBottom: 4 }}>SPILL CANDIDATES</div>
          <div style={{ fontSize: '20px', fontWeight: 700, color: analysis.spills.length > 0 ? 'var(--accent-red)' : 'var(--accent-green)' }}>
            {analysis.spills.length}
          </div>
          <div style={{ fontSize: '11px', color: 'var(--text-secondary)' }}>Spilled to memory stack</div>
        </div>
      </div>

      <div style={{ display: 'grid', gridTemplateColumns: '1.2fr 1fr', gap: 16 }}>
        {/* Liveness Table & Coloring */}
        <div style={{ background: 'var(--bg-secondary)', padding: '14px', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)' }}>
          <div style={{ fontSize: '12px', fontWeight: 600, color: 'var(--text-secondary)', marginBottom: 12, display: 'flex', alignItems: 'center', gap: 6 }}>
            <Activity size={14} /> LIVE RANGES & CHAITIN-BRIGGS ALLOCATION
          </div>
          <table style={{ width: '100%', borderCollapse: 'collapse', fontSize: '12px' }} className="mono">
            <thead>
              <tr style={{ borderBottom: '1px solid var(--border-color)', color: 'var(--text-muted)' }}>
                <th style={{ padding: '6px 8px', textAlign: 'left' }}>Variable</th>
                <th style={{ padding: '6px 8px', textAlign: 'left' }}>Type</th>
                <th style={{ padding: '6px 8px', textAlign: 'left' }}>Live Range</th>
                <th style={{ padding: '6px 8px', textAlign: 'left' }}>Assigned Hardware Reg</th>
              </tr>
            </thead>
            <tbody>
              {Object.entries(analysis.live_ranges).map(([v, range]) => {
                const reg = analysis.allocations[v];
                const isTemp = v.startsWith('t');
                return (
                  <tr key={v} style={{ borderBottom: '1px solid var(--border-color)' }}>
                    <td style={{ padding: '6px 8px', fontWeight: 600, color: isTemp ? 'var(--accent-purple)' : 'var(--accent-cyan)' }}>
                      {v}
                    </td>
                    <td style={{ padding: '6px 8px', color: 'var(--text-muted)' }}>
                      {isTemp ? 'Compiler Temp' : 'Program Var'}
                    </td>
                    <td style={{ padding: '6px 8px', color: 'var(--text-primary)' }}>
                      [inst {range.start} → {range.end}] ({range.duration} insts)
                    </td>
                    <td style={{ padding: '6px 8px' }}>
                      {reg ? (
                        <span className="badge badge-green">{reg}</span>
                      ) : (
                        <span className="badge badge-red">SPILL</span>
                      )}
                    </td>
                  </tr>
                );
              })}
            </tbody>
          </table>
        </div>

        {/* Interference Edges Matrix */}
        <div style={{ background: 'var(--bg-secondary)', padding: '14px', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-color)' }}>
          <div style={{ fontSize: '12px', fontWeight: 600, color: 'var(--text-secondary)', marginBottom: 12, display: 'flex', alignItems: 'center', gap: 6 }}>
            <Server size={14} /> REGISTER INTERFERENCE GRAPH EDGES ({analysis.interference_edges.length} edges)
          </div>
          <div style={{ fontSize: '12px', color: 'var(--text-muted)', marginBottom: 8 }}>
            Variables that are simultaneously live cannot share the same hardware register:
          </div>
          <div style={{ maxHeight: '300px', overflowY: 'auto', display: 'flex', flexWrap: 'wrap', gap: 6 }}>
            {analysis.interference_edges.map((e, idx) => (
              <div
                key={idx}
                className="mono"
                style={{
                  padding: '4px 8px',
                  background: 'var(--bg-tertiary)',
                  borderRadius: 'var(--radius-sm)',
                  fontSize: '11px',
                  border: '1px solid var(--border-color)',
                  display: 'flex',
                  alignItems: 'center',
                  gap: 6,
                }}
              >
                <span style={{ color: 'var(--accent-cyan)' }}>{e.source}</span>
                <span style={{ color: 'var(--accent-amber)' }}>⚡ interferes with</span>
                <span style={{ color: 'var(--accent-cyan)' }}>{e.target}</span>
              </div>
            ))}
          </div>
        </div>
      </div>
    </div>
  );
};
